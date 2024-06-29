# Description:
File search project
The settings and answers files are located in directory JSON.
The "config" file specifies the project name, version, the maximum number of output results, as well as files to search in the format: 
```
{
   "config": {
     "name": "Json_finder",
     "version": "0.1",
     "max_responses": 5
   },
   "files": [
     "..//file001.txt",
     "..//file002.txt",
     "../resources/file003.txt",
     "../resources/file004.txt"
   ]
}
```
Search words are specified in the "request" file in the following format:
```
{
   "requests": [
     "some words..",
     milk,
     milk sugar,
     "sugar",
     "somebody.."
   ]
}
```
The parsed text must be in plain text format in the files specified in "config"

After analysis, the results are recorded in the answers file in the following format:
```
{
"answers":[
	{"request0":
		["result","false"]},
	{"request1":[
		["result","true"],
		{"relevance":[
			["docid",0],["rank",1.0],
			["docid",1],["rank",0.5]]}]},
	{"request2":[
		["result","true"],
		{"relevance":[
			["docid",0],["rank",1.0],
			["docid",1],["rank",0.75]]}]},
	{"request3":[
		["result","true"],[
		["docid",0],["rank",1.0]]]},
	{"request4":
		["result","false"]}]
}
```
Where, "request" means the search word with a number corresponding to the ordinal in the "request" file. "result" displays the result of the search, where true means one or more results and false means none.
After this item, the search result is displayed or, if there is more than one result, the "relevance" heading and the results following it.
"docid" displays the sequence number of the result in the chain.
"rank" indicates the relative relevance of the query in the given document.


# About the project
The project is divided into functional elements, each of which performs its function.
* converter_JSON.h contains the Converter_JSON class, which is responsible for all work with JSON (reading from "config", "request" and writing to "answers").
* inverted_index.h contains the InvertedIndex class, which is responsible for reading text data from text files and assigning an index to their content in the match record.
* search_server.h contains the SearchServer class, which checks the correspondence between requests and file content using the data prepared by the InvertedIndex class and compiles relevancy indexes for them.
* projects_source.h contains all the included libraries and auxiliary files, including those described above, and also contains auxiliary structures for the InvertedIndex and SearchServer classes.
* exception_source.h contains all provided exceptions for abnormal situations of the program.
The project used a library not contained in the standard library - nlohmann. It is designed to work with JSON and plays a key role in reading and writing.

# Project setup
You need to download the project, fill in all the files (except "answers", of course), and then run the program through the compiler or through the terminal command ./build.sh that will assemble? compile and run the programm and testes, and the program will write the result to the file.