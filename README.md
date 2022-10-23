Mini project : Creating a contacts directory using hashtables and linked lists.

The code is detailed with a lot of comments(in french) 
 
To test the code :

	$cd <name of repository where you have all the project files> 

	$make 

	$cd tests 

	$./directory-01-test #for the first test for example

TESTS : $cd tests 

	directory-01 : memory test (check if the free_dir function works well) 

	directory-02 : check if the insertion in the hash table works 

	directory-03 : same as directory-02, but with three contacts 

	directory-04 : check if the dir_lookup_num function is working 

	directory-05 : check if the dir_delete function is working. 

	directory-06 : redimensioning test : adding a lot of contacts (as a result we will double the hash table size) 

	directory-07 : redimensioning test : deleting contacts, ( as a result the hashtable will shrink). 

And of course you can add your own tests, an extension maybe? 

To see if there are any memory leaks, you can use Valgrind :

	$valgrind ./tests/directory-01-test #for the first test for example.
