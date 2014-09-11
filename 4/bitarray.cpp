#include "lp.h"

#define BITS_PER_BYTE       8

/*
 * Purpose: To initialize a bit array for use and set its initial size.
 */
BitArray::BitArray (ULong pSizeInBits)
{
    vArray           = NULL;
    vCapacityInBytes = 0;
    if (pSizeInBits > 0) EnsureCapacity (pSizeInBits);
}

BitArray::~BitArray ()
{
    delete vArray;
}

/*
 * Purpse: To set the max size of bit array.
 * Notes:
 *      1. Does not preserve or modify existing data.
 */
bool BitArray::EnsureCapacity (ULong pSizeInBits)
{
        ULong nbytes;

    // Expand array if needed
    nbytes = (pSizeInBits/BITS_PER_BYTE) + 1;
    if (nbytes > vCapacityInBytes) {
        // Release existing array and create new array.
        delete vArray;
        vArray = new Byte[pSizeInBits];
        vCapacityInBytes = nbytes;
        ResetAllBits ();
    }
    return true;
}

/*
 * Purpose: To release memory allocated for the bit array.
 */
void BitArray::Destroy (void)
{
    if (vArray) delete (vArray);
    vArray           = NULL;
    vCapacityInBytes = 0;
}

/*
 * Purpose: To check if a bit is set.
 */
Word BitArray::GetBit (ULong pBit)
{
        ULong byte;
        ULong mask;

    byte = pBit/BITS_PER_BYTE;
    assert (byte < vCapacityInBytes);

    mask = (1 << (pBit % BITS_PER_BYTE));
    return (vArray[byte] & mask) ? 1 : 0;
}

/*
 * Purpose: To set a bit.
 */
void BitArray::SetBit (ULong pBit)
{
        ULong byte;
        ULong mask;

    byte = pBit/BITS_PER_BYTE;
    assert (byte < vCapacityInBytes);

    mask = (1 << (pBit % BITS_PER_BYTE));
    vArray[byte] |= mask;
}

/*
 * Purpose: To reset a bit.
 */
void BitArray::ResetBit (ULong pBit)
{
        ULong byte;
        ULong mask;

    byte = pBit/BITS_PER_BYTE;
    assert (byte < vCapacityInBytes);

    mask = ~(1 << (pBit % BITS_PER_BYTE));
    vArray[byte] &= mask;
}

/**
 * Purpose: To reset all bits.
 */
void BitArray::ResetAllBits ()
{
    memset (vArray, 0, vCapacityInBytes);
}
