
# Utility

## setStatusMessage 

                template <typename... Args> // 0 or multiple arguments of different type  
                void setStatusMessage(std::format_string<Args...> msg, Args&&...args ){ 
                  E.statusMessage = std::format(msg,std::forward<Args>(args)...);
                };

This ones kinda a mess

written purely of my understanding could be stupidly wrong but works for now 

- templates needs to be defined at .h files itself so compiler can read and assign arge type or somethign like that 

- so template<typename... Args> - similar to normal template but instead of one type , _typename... Args_ allows 0 or multiple args-

- std::format_string is used instead of regular string or string_view since it calls error at compile time incase passed data cant be formated 

- Args&&... args = points to actual values of all types 

- std::forward - basically move instead of copy if possible ( minor optimisation in this case )


## Trim utils 

### is_not_space 

        static inline bool is_not_space(char c){
          return c == ' ' ? false : true;
        }

- *static* - this function can only be used within this file 
- *inline* - to my understanding, code reduced at compile time to reduce overhead

### ltrim 

        void ltrim(std::string &s){
          auto first_non_space = std::find_if(s.begin(), s.end(),is_not_space); 
          s.erase(s.begin(),first_non_space); 
        };


- *std::string& s* - original string is getting modified no copies made

### rtrim 

        void rtrim(std::string &s){
          auto last_non_space = std::find_if(s.rbegin(), s.rend(),is_not_space);
          s.erase(last_non_space.base(),s.end());
        };

- *rbegin* & *rend* - basically reverse the iterator and loop backwords 
- *base()* - resets iterator

### trim 

I dont think i need to explain that, if you need one 
Im disappointed in you future ME 
