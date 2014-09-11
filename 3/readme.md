Solution to the stable marriage problem.

Uses a multi-pass algorithm. In each pass, each boy 'proposes' to his most-preferred
partner. The most-preferred partner is defines as the girl most-preferred girl who
is not yet married. If the boy is the most-preferred for the girl (using the same definition
of most-preferred), they are married, else the two are engaged. If another boy proposes to
an engaged girl and the boy is the highest-preferred, the engagment is broken and the girl
girl marries the other boy.

If after a pass, a boy is still engaged to the girl he proposed, he moves on to proposing the
next most-preferred girl.

We keep iterating till every boy is married.
