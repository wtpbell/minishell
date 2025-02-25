// int exec_block(t_ast_node *node)
// {
//		int status_;
//		pid_t pid;
//		printf("exec_block: Entering\n");
//		signal(SIGINT, interrput_slience);
//		signal(SIGQUIT, interrput_slience);
//		pid = fork();
//		if (pid == -1)
//		{
//			error("fork() failed", NULL);
//			return (EXIT_FAILURE);
//		}
//		else if (pid == 0)  // Child process
//		{
//			printf("exec_block: In child process\n");
//			signal(SIGINT, SIG_DFL);
//			signal(SIGQUIT, SIG_DFL);
//		status_ = executor_status(node->left);
//		printf("exec_block: Child process exiting with status %d\n", status_);
//		set_exit_status(status_);
//		free_all_memory();
//		exit(status_); // 🔥 Ensure correct exit status
//	}
//		// Parent process waits for the subshell
//		printf("exec_block: Parent waiting for child process\n");
//		wait(&status_);
//		printf("exec_block: After waitpid, raw status = %d\n", status_);
//		// Extract correct exit status
//		if (WIFEXITED(status_))
//		{
//         status_ = WEXITSTATUS(status_);
//         printf("exec_block: Subshell exited normally, exit status = %d\n", status_);
//		}
//		else
//		{
//         status_ = EXIT_FAILURE;
//         printf("exec_block: Subshell exited abnormally\n");
//		}
//		set_exit_status(status_);
//		signals_init();
//		printf("exec_block: Returning status %d\n", status_);
//		return (status_);
// }


// void executor(t_ast_node *node) //for checking
// {
// 	int i;

// 	if (!node)
// 	{
// 		printf("executor: received NULL node\n");
// 		return ;
// 	}
// 	printf("executor: processing node of type %d\n", node->type);
// 	if (node->args)
// 	{
// 		printf("executor: command = %s\n", node->args[0]);
// 		printf("executor: arguments = ");
// 		for (i = 0; node->args[i]; i++)
// 		printf("\"%s\" ", node->args[i]);
// 		printf("\n");
// 	}

// 	set_exit_status(executor_status(node));
// }

// void	executor(t_ast_node *node) // For checking redir
// {
// 	int i;
// 	t_redir *redir;

// 	if (!node)
// 	{
// 		printf("executor: received NULL node\n");
// 		return ;
// 	}
// 	// Checking for redirections
// 	if (node->type == 19)
// 	{
// 		redir = node->redirections;
// 		printf("executor: processing redirections\n");
// 		while (redir)
// 		{
// 			if (redir->type == TOKEN_REDIR_IN)
// 				printf("executor: input redirection from file: \"%s\"\n", redir->file);
// 			else if (redir->type == TOKEN_REDIR_OUT)
// 				printf("executor: output redirection to file: \"%s\"\n", redir->file);
// 			else if (redir->type == TOKEN_HEREDOC)
// 				printf("executor: heredoc redirection with file: \"%s\"\n", redir->file);
// 			else if (redir->type == TOKEN_APPEND)
// 				printf("executor: append redirection to file: \"%s\"\n", redir->file);

// 			redir = redir->next;
// 		}
// 	}
// 	// For pipe node processing
// 	if (node->type == 1)
// 	{
// 		printf("executor: processing pipe node\n");
// 		if (node->left)
// 		{
// 			printf("executor: left command = %s\n", node->left->args ? node->left->args[0] : "NULL");
// 			if (node->left->args)
// 			{
// 				for (i = 0; node->left->args[i]; i++)
// 					printf("executor: left argument %d: \"%s\"\n", i, node->left->args[i]);
// 			}
// 		}
// 		if (node->right)
// 		{
// 			printf("executor: right command = %s\n", node->right->args ? node->right->args[0] : "NULL");
// 			if (node->right->args)
// 			{
// 				for (i = 0; node->right->args[i]; i++)
// 					printf("executor: right argument %d: \"%s\"\n", i, node->right->args[i]);
// 			}
// 		}
// 	}
// 	else // Regular command node
// 	{
// 		printf("executor: processing command node of type %d\n", node->type);
// 		if (node->args)
// 		{
// 			printf("executor: command = %s\n", node->args[0]);
// 			printf("executor: arguments = ");
// 			for (i = 0; node->args[i]; i++)
// 				printf("\"%s\" ", node->args[i]);
// 			printf("\n");
// 		}
// 	}
// 	set_exit_status(executor_status(node));
// }



// int	check_cmd(t_ast_node *node) //for debug
// {
// 	int	status_;

// 	printf("\n=== Command Check ===\n");
// 	printf("PID: %d - Checking command: %s\n", getpid(), node->args[0]);
//     // Handle PATH=NULL case
// 	if (get_env_value(*node->env, "PATH") == NULL && 
// 		node->args[0][0] != '/' && node->args[0][0] != '.')
// 	{
// 		append_cwd(node);
// 		printf("PID: %d - No PATH, appended CWD: %s\n", getpid(), node->args[0]);
// 	}
// 	printf("PID: %d - Processing command: %s\n", getpid(), node->args[0]);

//     // Handle relative/absolute paths vs PATH resolution
// 	if (node->args[0][0] != '/' && node->args[0][0] != '.')
// 	{
// 		printf("PID: %d - Resolving command via PATH: %s\n", getpid(), node->args[0]);
// 		status_ = resolve_command(node);
// 		if (status_ != 0)
// 		{
// 			printf("PID: %d - Command resolution failed: %s\n", getpid(), node->args[0]);
// 			return (status_);
// 		}
//         printf("PID: %d - Resolved to: %s\n", getpid(), node->args[0]);
// 	}
// 	else
// 	{
// 		printf("PID: %d - Validating executable: %s\n", getpid(), node->args[0]);
// 		status_ = validate_executable(node);
// 		if (status_ != 0)
// 		{
// 			printf("PID: %d - Executable validation failed: %s\n", getpid(), node->args[0]);
// 			return (status_);
// 		}
// 	}
// 	printf("PID: %d - Command check successful: %s\n", getpid(), node->args[0]);
// 	printf("==================\n\n");
// 		return (0);
// }
