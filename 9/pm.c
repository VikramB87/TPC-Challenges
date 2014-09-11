#include <stdio.h>
#include <assert.h>
#include <windows.h>

#define NDEBUG

#define MAX_LENGTH 256
#define SLASH_STAR '\n'
#define SLASH_SLASH '\\'
#define SLASH_Q     '\r'
#define MAX_TEXT   400000
#define MAX_PAT    10000

#define MASK_SIZE 32  //(256/8)
#define MASK_SIZE_SHIFT 5

typedef struct {
    char *begin;
    char *end;
} String;

typedef struct _pattern {
    int    deleted;
    String str;
    String substr;
    struct _pattern *next;
} Pattern;

typedef unsigned char Byte;

char* rev_sub_pat_match (String *text, String *pattern);

char gWords[MAX_TEXT][MAX_LENGTH];
char gPatterns[MAX_PAT][MAX_LENGTH];
String gText[MAX_TEXT];
Byte gTextMask[MAX_TEXT][MASK_SIZE];
int gNumWords;
int gNumPatterns;
char gMatchTable[256];

int string_len (String *s)
{
    return (s->end - s->begin);
}

int check_mask (Byte mask[MASK_SIZE], char *str)
{
    Byte c;
    while ((c = *str)) {
        if (!(mask[c >> MASK_SIZE_SHIFT] & (1 << (c&7)))) return 0;
        ++str;
    }
    return 1;
}

void init_match_table ()
{
    int i;
    int c;
    for (i = 0; i < 256; i++) {
        if (i >= 'A' && i <= 'Z') c = i+32;
        else if (i == '*') c = SLASH_STAR;
        else if (i == '?') c = SLASH_Q;
        else if (i == '\\') c = SLASH_SLASH;
        else c = i;

        gMatchTable[i] = c;
    }
}

int alpha_match (char t, char p)
{
    return (gMatchTable[t] == p);
}


int pattern_match (String *text, Pattern *pattern, Byte mask[MASK_SIZE])
{
    char *t = text->begin;
    char *p;
    char *tm;
    String sp;
    String st;

    if (!pattern || pattern->deleted) return !*t;

    if (!check_mask (mask, pattern->str.begin)) return 0;

    p = pattern->str.begin;

    while ((t != text->end) && (p != pattern->str.end)) {

        switch (*p) {
            case '*':
                if (!*(pattern->substr.begin)) return 1;
                st.begin = t, st.end = text->end;
            submatch:
                if (!(st.begin = rev_sub_pat_match (&st, &pattern->substr))) return 0;
                st.begin += string_len (&pattern->substr);
                st.end = text->end;
                if (pattern_match (&st, pattern->next, mask)) return 1;
                st.end = st.begin - string_len (&pattern->substr);
                st.begin = t;
                goto submatch;
                break;
            case '?':
                break;

            default:
                if (!alpha_match (*t, *p)) return 0;
        }

        t++;p++;
    }

    if (t == text->end) {
        if (p == pattern->str.end) return 1;
        if (*p == '*' && !*(pattern->substr.begin)) return 1;
    }
    return 0;
}

char* rev_sub_pat_match (String *text, String *pattern)
{
    char *s = text->end-1;
    char *t;
    char *p;

    while (s > (text->begin-1)) {
        t = s;
        p = pattern->end-1;
        while ((t > (text->begin-1)) && (p > (pattern->begin-1))) {
            //assert (*p != '*');
            switch (*p) {
                case '?':
                    break;
                default:
                    if (!alpha_match (*t, *p)) goto next;
            }
            t--;p--;
        }
next:
        if (p < pattern->begin) return t+1;
        s--;
    }
    return NULL;
}

void preprocess_pattern (char *str, Pattern *pat)
{
    char *p;
    char *s;

    pat->str.end = str + _tcslen(str);

    p = str;
    while (*p != '\n') {
        if (*p == '\\') {
            switch (*(p+1)) {
                case '?':
                    *p = SLASH_Q; break;
                case '*':
                    *p = SLASH_STAR; break;
                default:
                    *p = SLASH_SLASH; break;
            }
            memmove (p+1, p+2, pat->str.end - (p+2));
        } else if (*p == '*') {
            s = p;
            while (*(s+1) == '*') s++;
            if (s > p) memmove (p+1, s+1, pat->str.end - s);
        } else {
            *p = tolower(*p);
        }

        p++;
    }

    *p = 0;
    pat->str.end = p;
}

void process_pattern (char *str, Pattern *pat)
{
    char *p;
    char *s;

    pat->deleted = 0;
    pat->str.begin = str;
    pat->str.end = str + _tcslen(str);
    if (pat->next) pat->next->deleted = 1;

    p = str;
    while (*p) {
        if (*p == '*') {
            s = p+1;
            while (*s && *s != '*') s++;
            pat->substr.begin = p+1;
            pat->substr.end = s;
            if (*s) {
                if (!pat->next) pat->next = (Pattern*) malloc (sizeof(Pattern));
                pat->next->next = NULL;
                process_pattern (s, pat->next);
            }
            return;
        }
        p++;
    }
}

void process_text (char *str, String *text, Byte mask[MASK_SIZE])
{
    Byte c;
    text->begin = str;
    while (*str != '\n') {
        c = gMatchTable[*str];
        mask[c >> MASK_SIZE_SHIFT] |= (1 << (c&7));
        str++;
    }
    *str = 0;
    text->end = str;
    c = '*';
    mask[c >> MASK_SIZE_SHIFT] |= (1 << (c&7));
    c = '?';
    mask[c >> MASK_SIZE_SHIFT] |= (1 << (c&7));
}

DWORD WINAPI ThreadProc (void *pParam)
{
    int i;
    for (i = gNumWords/2 + 1; i < gNumWords; i++) {
        process_text (gWords[i], &gText[i], gTextMask[i]);
    }

    *(int*) pParam= count_matches (gNumPatterns/2+1, gNumPatterns-1);
    return 0;
}

int count_matches (int from, int to)
{
    Pattern pattern;
    int count = 0;
    int i;
    int j;


    pattern.next = NULL;
    for (j = from; j <= to; j++) {
        preprocess_pattern (gPatterns[j], &pattern);
        process_pattern (gPatterns[j], &pattern);
        for (i = 0; i < gNumWords; i++) {
            if (pattern_match (&gText[i], &pattern, gTextMask[i])) {
                count++;
            }
        }
    }
    return count;
}


int main (int argc, char *argv[])
{
    int display = 0;
    char *tfn, *pfn;
    FILE *txtfile, *patfile;
    int i;
    char pat[MAX_LENGTH];
    Pattern pattern;
    char *c;
    int count = 0;
    int count1;
    int s;
    int j;
    HANDLE h;

/*    while (1) {
        scanf ("%s%s", s, p);
        t.begin = s;
        t.end = s + _tcslen(s) ;
        preprocess_pattern (p, &pat);
        if (pattern_match (&t, &pat)) {
            printf ("Yes!\n");
        } else {
            printf ("No.\n");
        }
    } */

    if (argc < 3 || argc > 4) {
        fprintf (stderr, "Invalid arguments.\n");
        fprintf (stderr, "Usage: %s [-d] <input-file> <pattern-file>", argv[0]);
        return 1;
    }

    if (argc == 4) display = 1;

    tfn = display ? argv[2] : argv[1];
    if (!(txtfile = fopen (tfn, "r"))) {
        fprintf (stderr, "Failed to open %s!\n", tfn);
        return 1;
    }

    pfn = display ? argv[3] : argv[2];
    if (!(patfile = fopen (pfn, "r"))) {
        fprintf (stderr, "Failed to open %s!\n", pfn);
        return 1;
    }

    init_match_table ();

    while (fgets (gWords[gNumWords], MAX_LENGTH, txtfile)) {
        gNumWords++;
    }

    while (fgets (gPatterns[gNumPatterns], MAX_LENGTH, patfile)) {
        gNumPatterns++;
    }


    if (display) {
        pattern.next = NULL;
        for (i = 0; i < gNumWords; i++) {
            process_text (gWords[i], &gText[i], gTextMask[i]);
        }
        for (j = 0; j < gNumPatterns; j++) {
            preprocess_pattern (gPatterns[j], &pattern);
            process_pattern (gPatterns[j], &pattern);
            for (i = 0; i < gNumWords; i++) {
                if (pattern_match (&gText[i], &pattern, gTextMask[i])) {
                    count++;
                    printf ("%s\n", gText[i].begin);
                }
            }
            printf ("\n");
        }
        printf ("%ld\n", count);
    } else {

        h = CreateThread (NULL, 0, ThreadProc, &count1, 0, NULL);

        for (i = 0; i < gNumWords/2; i++) {
            process_text (gWords[i], &gText[i], gTextMask[i]);
        }

        count = count_matches (0, gNumPatterns/2);
        WaitForSingleObject (h, INFINITE);
        printf ("%ld\n", count+count1);
        CloseHandle (h);
    }


    fclose(txtfile);
    fclose(patfile);
    return 0;
}
