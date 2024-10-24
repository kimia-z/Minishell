#include "lexer.h"
#include "parser.h"
#include "minishell.h"

// history is loaded from a file - read and loaded from a file
// have history as a linked list for immediate access and then write off to a file later
// if we decided to save hsitory to a file we could use these fuctions



void add_history_node(t_historylist *history, const char *command)
{
    t_historynode *new_node;
    new_node = (t_historynode *)malloc(sizeof(t_historynode));
    if (!new_node)
    {
        perror("malloc");
        return;
    }
    new_node->command = strdup(command);
    new_node->next = NULL;
    if (history->tail)
        history->tail->next = new_node;
    else
        history->head = new_node;
    history->tail = new_node;
}


static int open_file(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        if (errno != ENOENT)
            perror("open");
    }
    return fd;
}

static void process_line(t_historylist *history, char *line)
{
    add_history_node(history, line);
    add_history(line); // add to Readline history
}


static void read_lines(int fd, t_historylist *history)
{
    char buffer[1024];
    ssize_t bytes_read;
    char *line = NULL;
    size_t len = 0;

    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
    {
        for (ssize_t i = 0; i < bytes_read; i++)
        {
            if (buffer[i] == '\n')
            {
                if (line)
                {
                    line[len] = '\0';
                    process_line(history, line);
                    free(line);
                    line = NULL;
                    len = 0;
                }
            }
            else
            {
                line = realloc(line, len + 2);
                if (line == NULL)
                {
                    perror("realloc");
                    close(fd);
                    return;
                }
                line[len++] = buffer[i];
            }
        }
    }
    if (line)
    {
        line[len] = '\0';
        process_line(history, line);
        free(line);
    }
}



static void close_file(int fd)
{
    close(fd);
}


void load_history(t_historylist *history, const char *filename)
{
    int fd = open_file(filename);
    if (fd == -1)
        return;

    read_lines(fd, history);
    close_file(fd);
}

// save history from the linked list to a file
void save_history(t_historylist *history, const char *filename)
{
    int fd;
    t_historynode *current;
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror("open");
        return;
    }

    current = history->head;
    while (current)
    {
        write(fd, current->command, strlen(current->command));
        write(fd, "\n", 1);
        current = current->next;
    }

    close(fd);
}

// free the history linked list
void free_history(t_historylist *history)
{
    t_historynode *next;
    t_historynode *current;

    current = history->head;
    while (current)
    {
        next = current->next;
        free(current->command);
        free(current);
        current = next;
    }
    history->head = NULL;
    history->tail = NULL;
}
