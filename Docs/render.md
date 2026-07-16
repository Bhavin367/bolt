
# Render

## setMessage 

                template <typename... Args> // 0 or multiple arguments of different type  
                void setMessage(std::format_string<Args...> msg, Args&&...args ){ 
                  E.statusMessage = std::format(msg,std::forward<Args>(args)...);
                };

This ones kinda a mess

written purely of my understanding could be stupidly wrong but works for now 

- templates needs to be defined at .h files itself so compiler can read and assign arge type or somethign like that 

- so template<typename... Args> - similar to normal template but instead of one type , _typename... Args_ allows 0 or multiple args-

- std::format_string is used instead of regular string or string_view since it calls error at compile time incase passed data cant be formated 

- Args&&... args = points to actual values of all types 

- std::forward - basically move instead of copy if possible ( minor optimisation in this case )
