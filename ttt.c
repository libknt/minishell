#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>	// fork/wait
#include <unistd.h>	// fork/sleep
#include <sys/wait.h>	// fork/wait

#include <err.h>
#include <errno.h>

pid_t
Fork ()
{
	pid_t	pid;

	pid = fork ();
	if (-1 == pid)
	{
		warn ("can not fork");
	}
	return (pid);
}

void
child ()
{
	(void) sleep (1);
	(void) printf ("child: pid=%d\n", getpid () );
	(void) fflush (stdout);
}

void
multi_fork ()
{
	int	i = 0;
	int	max = 10;

	for (i = 0; i < max; ++i)
	{
		pid_t pid = Fork ();
		if (-1 == pid)
		{
			break;
		}
		else if (0 == pid)
		{
			// child
			child ();
			exit (EXIT_SUCCESS);
			/* NOTREACHED */
		}
	}
}

void
multi_wait ()
{
	for ( ; ; )
	{
		pid_t	pid;
		int	status = 0;

		pid = wait (& status);

		if (pid == -1)
		{
			if (ECHILD == errno)
			{
				// 子プロセスが存在しない
				break;
			}
			else if(EINTR == errno)
			{
				continue;
			}
			// wait が失敗した
			err (EXIT_FAILURE, "wait error");
		}
		(void) printf ("parent: child = %d, status=%d\n", pid, status);
	}
}

int
main(int argc, char *argv[])
{
	multi_fork ();
	sleep (2);	// 少し待つ
	multi_wait ();

	exit (EXIT_SUCCESS);
}
