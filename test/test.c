#include <stdio.h>
# include <termios.h>
# include <term.h>
# include <curses.h>
#include <unistd.h>

# define KEY_R "\x1b\x5b\x43\x0\x0\x0"
# define KEY_L "\x1b\x5b\x44\x0\x0\x0"
# define KEY_UP_ "\x1b\x5b\x41\x0\x0\x0"
# define KEY_DOWN_ "\x1b\x5b\x42\x0\x0\x0"

int tputs_output(int i)
{
	return ((int)write(1, &i, 1));
}


int		ft_isprint(int c)
{
	return ((c >= ' ' && c <= '~') ? 1 : 0);
}

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (*s1 == *s2 && ++i < n)
	{
		if (*s1 == '\0' && *s2 == '\0')
			return (1);
		if (*s1 == '\0' || *s2 == '\0')
			return (0);
		s1++;
		s2++;
	}
	if (n == 0 || *s1 == *s2)
		return (1);
	return (0);
}


int main(void){ 
    char old_c = 0;
    int c;
    static struct termios oldt, newt;
    char line[256];
    int i = 0;
    int flag = 0;

    char buff[256];


    line[255] = '\0';
    char escape[3];

    tcgetattr( STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHOCTL);
    // newt.c_oflag &= ~(ONLCR);
    // newt.c_cc[VERASE] = '\b';

    tcsetattr( STDIN_FILENO, TCSANOW, &newt);


    while((c = getchar()) != '!')
    {
        line[i] = c;
        i++;
        if (i == 255)
            break;

        escape[0] = escape[1];
        escape[1] = escape[2];
        escape[2] = c;


        // if (ft_strnequ(escape, KEY_L, 3))
        // {
        //     write(1, "<", 1);
        //     write(1, escape, 3);
        // }
        // else if (ft_strnequ(escape, KEY_R, 3))
        //     // write(1, ">", 1);
        // else if (ft_strnequ(escape, KEY_UP_, 3))
        //     // write(1, "^", 1);
        // else if (ft_strnequ(escape, KEY_DOWN_, 3))
        //     // write(1, "v", 1);

        if (c == 127)
        {
            // printf("escape: %d..%d..%d\n", escape[0], escape[1], escape[2]);
            write(1, "\b", 1);
            // putchar(27);
            // putchar(91);
            // putchar(68);
            // putchar(' ');
            // putchar(27);
            // putchar(91);
            // putchar(68);
            // write(1, &c, 1);
            // i = -1;
            // printf("\033[33mDEL: ");
            // while (newt.c_cc[++i])
            //     printf("%d  ", newt.c_cc[i]);
            // printf("\033[0m\n");
        }

        // if (c == 27)
        //     flag = 1;
        // else if (flag == 1 && c == 91)
        //     flag = 2;
        // else if (flag == 2 && c == 67)
        // {
        //     write(1, "#", 1);
        //     flag = 0;
        // }
    }

    printf("catch: %c\n", c);

    i = 0;
    while (line[i])
    {
        if (ft_isprint(line[i]))
            printf("'%c'->", line[i]);
        else
            printf("\033[32mctl->");
        
        printf("%3d \033[0m| ", line[i]);

        i++;

        if (i % 10 == 0)
            printf("\n");
        // write(1, &line[i], i);
        
    }
    printf("\n");
    // printf("finally: %s\n", line);

    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);


    return 0;
}

