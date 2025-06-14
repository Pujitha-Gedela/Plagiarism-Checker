Plagiarism-Checker
A simple C++ program that checks for plagiarism between two text files by comparing phrases (not just words!). This helps identify if large portions of text are copy-pasted — even if they appear slightly scattered across paragraphs.
What's the idea?
This project simulates how basic plagiarism detection works using programming logic. It doesn’t use AI or large databases — it focuses on comparing **word sequences** between two files and finding matches.
It helps visualize and understand how real-world plagiarism detection starts — by checking for overlapping patterns in text.

What it actually does
1. You give it two text files.
2. It reads and breaks them into words.
3. It forms **small word windows** (e.g., 5 words at a time).
4. It checks if any of these word windows appear in both files.
5. Finally, it shows:
   - Number of matches
   - Plagiarism percentage (based on matching chunks)

Tech Used
- C++ for fast string and file processing
- Standard Template Library (STL): `vector`, `string`, `unordered_set`
- Rolling Hash algorithm for fast phrase comparison
- VS Code + g++ for development and compilation
- GitHub for version control and publishing

 
