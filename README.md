Bonjour,

Pour faire les tests, faut faire un $make dans le répertoire filrouge,
puis lancer les executables directory-01-test, directory-02-test ....

le format ----------  case i ------------ est juste pour la bonne visualisation de toutes les  cases de l'annuaire (même les cases vides)
          -------------------------------

Remarque concernant le test de retrecissement: directory-07-test
on crée un annuaire de taille 20. quand on insere le premier contact, l'annuaire se redimensionne parce que 1 contact < 15% de la taille
donc on aura un annuaire de 10 cases enfin

Vous pouvez faire des tests de mémoires à l'aide de la commande $valgrind  (par exemple $valgrind ./tests/directory-01-test
 $valgrind ./tests/directory-02-test  ...etc )

Merci d'avance pour la correction et bon courage ;)
