Mini project : Creating a contacts directory using hashtables and linked lists.

The code is detailed with a lot of comments(in french) \n 
To test the code : \n
	$cd <name of repository where you have all the project files> \n
	$make \n
	$cd tests \n
	$./directory-01-test #for the first test for example \n
TESTS : $cd tests \n
	directory-01 : memory test (check if the free_dir function works well) \n
	directory-02 : check if the insertion in the hash table works \n
	directory-03 : same as directory-02, but with three contacts \n
	directory-04 : check if the dir_lookup_num function is working \n
	directory-05 : check if the dir_delete function is working. \n
	directory-06 : redimensioning test : adding a lot of contacts (as a result we will double the hash table size) \n
	directory-07 : redimensioning test : deleting contacts, ( as a result the hashtable will shrink). \n
And of course you can add your own tests, an extension maybe? 

To see if there are any memory leaks, you can use Valgrind : \\
	$valgrind ./tests/directory-01-test #for the first test for example.
