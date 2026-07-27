
### Completed Stuff 

- Basic vim and custom motions ( LEFT RIGHT UP DOWN PAGE_UP PAGE_DOWN HOME END )
- Numbering 
- File reading 
- Editor status bar - keeps track of total lines and cursor pos
- Editor message bar 
- Added enum class for editor modes with partial implementation 
- Added render rows for handling special cases like tabs Ctrl what not and also syntax highlighting 
- Now motions to right is cutt off based on rendered charactors instead of being infinitely right 

### Next Stuff 

(Order doesnt make sense now im just writing down all jargon)

- next we need proper text editing like insertion deleting, so expland on render part of erow
- more vim and custom motions ( next word, delete word, change word ) 
- syntax highlighting
- Proper implementation of modes , Editor , insert visual .
- File tree or side bar or whatever you call that 

- need work on rest of editor modes ( with text editing )
- add support for multiple arguments in command 

#### Jargon 

new approach for commands instead of having seperate read for commands ill just use default reading of 
editor and pass that to process commands 
