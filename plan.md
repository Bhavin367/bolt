
### Completed Stuff 

- Basic vim and custom motions ( LEFT RIGHT UP DOWN PAGE_UP PAGE_DOWN HOME END )
- Numbering 
- File reading 
- Editor status bar - keeps track of total lines and cursor pos
- Editor message bar 
- Added enum class for editor modes with partial implementation 

### Next Stuff 

(Order doesnt make sense now im just writing down all jargon)

- next we need proper text editing like insertion deleting, so expland on render part of erow
- more vim and custom motions ( next word, delete word, change word ) 
- fix vim motion acc to render rows 
- syntax highlighting
- Proper implementation of modes , Editor , insert visual .
- File tree or side bar or whatever you call that 

- need work on rest of editor modes ( with text editing )
- rewrite command.cpp and use main loop to execute it something like E.mode == command , processCommand() in  editorprocess key 


#### Jargon 

work on execute command function and maybe to add future support for multiple arguments im not removing all spaces 
but i gotta trim trailing white spaces and for now lets just add :q and work on rest after properly workign on text editing a bit more and file saving  
