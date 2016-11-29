# Word-Counter
Counts Words in a .txt file

Works on Windows only, due to the Windows standard library having support of unicode std::wstring.

This program scans a .txt file and counts the frequency of words in the text file. First it uses insertion sort to add all the words into
a vector, then it will use merge sort by frequency to show the most common words at top. Merge sort is used for stability during the sort.

After they're sorted, it will show some interesting statistics about the text file like uniqueness ratio, how many words, how many unique
words, and others.

TODO: Work on the "song generator" function to make more sensical songs using strategies such as stanza line counting, sentence length,
n-tuple recognition.
