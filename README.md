# minishell_42
A mini unix shell with basic functionalities

### Steps
  
  >### Lexing

 ```
 	typedef struct s_token
		{
			char			*value;
			int				type;
			bool			split;
			struct s_token	*next;
		}			t_token; 
```
>>#### Steps
	- WSPACE delimitation
      	- echo     arg1
	- echo $PATH "" '$PATH'

	- outputs
    	- TOKEN
    	- OPERATOR
    	- identify expandables

## Shell grammer
	- io_sym filename cmd args... | 
	- cmd io_sym filename args...
	- cmd args.. io_sym filename
	-  $?
	-  name=word
	-  


###	- Parsing
### - Execution