# Tokenisation

The following is an overview of how the shell will conduct the first stage of parsing - tokenisation.

## Idea

The idea is to use the `ft_split` function from the libft project, but using a custom charset and with the ability to treat the *stuff* within single (') and double (") quotes as a token on its own, to be parsed later down the line.

