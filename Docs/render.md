
# Render 

- Arguably the most annoying part 


### updateRow  

        void updateRow(erow &row){
          row.render.clear() ; 
          int idx = 0 ;
          
          for (char c : row.chars){
            if (c == '\t'){
              row.render.push_back(' '); // making sure theres ateast one space 
              ++idx; 
              while(idx % TAB_STOP != 0 ){
                row.render.push_back(' '); 
                ++idx ;  
              }; 
            }else {
              row.render.push_back(c);
              ++idx; 
            }; 
          };
        };

- Confusing part why isnt /t just render.push(' ') 8 times 
- cause unlike i assummed earlier tab stop are fixed spaced intervals 
- hence when we see a tab we advance to next interval to 8 spaces

        constexpr int TAB_STOP = 8 ; ( from type.h )

- different terminals have different intervals i assume although 8 is the standard like what im using here 


