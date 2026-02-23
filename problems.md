*Listes des tests defaillants*


	- echo Hello""World

	- echo "hello 'World" : la commande n est pas du tout execute.

	- si on fait uniquement : ou ! on lance une commande. le bash ne le lance pas.
	- si on fait uniquement / des leaks apparaissents.

	- si on commence directement la commande par un pipe ou a des doubles free + crash
		ex : | hello

	- notre programme n indique aucun message quand bash indique lui un message. exemple :
		minishell>$ ()
		minishell>$
		bash renvoi lui :
		bash-5.1$ ()
		bash: syntax error near unexpected token `)'

	- leak lorsque l on envoi uniquement ""
	- idem pour ''
	- idem pour .
	- idem pour ..


	- Segfault et crash quand on envoi uniquement *

	- echo $:$= rentre dans une boucle infinie. le programme apres ca n accepete plus aucune commande. un grand mystere !
	- >test> presente le meme probleme. impossible de refaire fonctionner le programme sans le quitter
	- idem pour >>test>>
	- idem pour <<test<<
	- idem pour echo $=HOME

	- probleme de quote avec echo(sera probablement regler avec le premier probleme)
		minishell>$ echo $''HOME
		$''HOME
		bash-5.1$ echo $''HOME
		HOME
		probleme avec toutes les commandes suivantes :
			- $> echo $"HOME"
			- $> echo '$HO'ME
			- $> echo "'$HO''ME'"
			- $> echo $"HO""ME"
			- $> echo $'HO''ME'
			- $> echo $'HOME'
			- $> echo "$"HOME
			- $> echo $"HELLO"
			- $> echo $'HELLO'

	- impossible de tester export car le = fait crash le programme.
	- probleme egalement avec les redirections.
	- taper juste cat nous genere le meme probleme qu avec un =


*certains resultats peuvent etre defendu en soutenance si on tombe pas sur un monstre.*

	- mauvaise indication du token posant probleme dans plusieur cas. un des exemples:
		minishell>$ &&
		minishell: syntax error near unexpected token `newline'
		on devrait avoir:
		bash-5.1$ &&
		bash: syntax error near unexpected token `&&'

	-si on tape juste ~ on a commande not found, bash renvoi :Is a directory

	- si on fait la commande sleep 3 | sleep 3 | sleep 3 puis ctrl c apres 3 seconde on constate un grand nombre de \n

	- env hello fait apparaitre l environnement alors que le bash dit no such file or directory
	(a voir ensemble si on bloque le nombre d arguement ou si on laisse comme ca)



















