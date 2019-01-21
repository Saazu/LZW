The Lempel-Ziv-Welch Algorithm

Each string W in the table is represented by a pair (C,K), where K is the
last character in W and C is the location in the table of the prefix of W
that contains all but the last character.  By convention, the null string is
at location EMPTY; and the components of the pair in location I are denoted
by PREF(I) and CHAR(I).
