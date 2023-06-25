/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoda <kyoda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:54:10 by keys              #+#    #+#             */
/*   Updated: 2023/06/25 14:31:02 by kyoda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_global;

static void	_err_arg(void)
{
	write(2, "Please run it with ./{ executable file name }.\n", 47);
	exit(127);
}

static void	func_readline(t_env **env, char *line, t_token *token, t_node *tree)
{
	while (1)
	{
		if (isatty(0))
			rl_event_hook = check_state;
		set_signal();
		line = readline("minishell>");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		token = lexer(&line, *env);
		if (token == NULL)
			continue ;
		expand_token(&token, *env, false);
		tree = parser(token, line);
		if (tree == NULL)
			continue ;
		exe_(tree, env);
		tree_free(tree);
		token_free(&token);
		free(line);
	}
}

static void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argv;
	if (argc != 1)
		_err_arg();
	env = NULL;
	make_lstenv(&env, envp);
	rl_outstream = stderr;
	func_readline(&env, NULL, NULL, NULL);
	free_env(env);
	return (g_global.exit_status);
}


/**
 * bash
 * 	-コマンドを入力して、解析して、実行する。
 * lexer
 * 	-コマンドの解析
 * 		-単語分割
 * 			- echo -e -n hello    echo | -e | -n | hello
 *		-error { || && ;; |& & ; ( ) | \n "" ''  } 
 * expand
 * 	- 変数展開
 * 		-{ 環境変数　”” ’’ } の展開
 * parser
 *  -コマンドの解析
 * 		-構文解析　 => 再起下降構文解析木
 * 			- コマンド　パイプ　リダイレクト　heredoc
 * 		- error { [ command || command ],  [リダイレクト] }
 * exe
 * 	-リダイレクト、heredocの実行
 * 	-コマンドの実行
 * 		- [ echo -e -n hello ] => echoのpathを探す  /bin/echo
 * 		-error 
 * 			[ 'ファイルがない' 'ファイルの権限がない' 'コマンドがない' ... ]
 * 		-buildin
 * 			-echo
 * 				-echo hello
 * 					-引数に与えられた文字列を標準出力に出力する
 * 				- echo -n hello
 * 					- [ -n ]
 * 						-改行なしで出力する
 * 			-pwd
 * 				-カレントディレクトリを表示する
 * 			-cd
 * 				-cd [path]
 * 				-カレントディレクトリを変更する
 * 			-env
 * 				-環境変数(valueのあるもの)を出力する
 * 			-export
 * 				- export
 * 					-環境変数(valueのないものも含める)を昇順で出力する
 * 				- export [key || key=value]
 * 					- 環境変数を更新する
 * 			-unset
 * 				-unset [環境変数(key)]
 * 				-設定された環境変数を削除する
 * 			-exit
 * 				-exit [終了ステータス]
 * 				- プロセスを終了する
 */