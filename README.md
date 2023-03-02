# Description:
File search project
The "config" file specifies the project name, version, the maximum number of output results, as well as files to search in the format: 
```
{
   "config": {
     "name": "endgame",
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
You need to download the project, fill in all the files (except "answers", of course), and then run the program through the compiler or through the terminal (the command is relevant for windows) using the start endgame command and the program will write the result to the file.

//////////////////////////////////////////////////////////////////////////////////////////////////

# Описание:
Проект по поиску слов в файлах
В файле "config" указываются название проекта, версия, максимальное количество выводимых результатов, а также файлы для поиска в формате: 
```
{
  "config": {
    "name": "endgame",
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
Слова для поиска указываются в файле "request"  в формате:
```
{
  "requests": [
    "some words..",
    "milk",
    "milk sugar",
    "sugar",
    ""somebody.."
  ]
}
```
Анализируемый текст должен находиться в обычном текстовом  формате в файлах, указанных в "config"

После анализа, результаты заносятся в файл answers в формате:
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
Где, "request" означае искомое слово с номером, соответственно порядковому в файле "request". "result" отображает итог поиска, где истина означает один и более результат, а ложь - ни одного.
После этого пункта отображается результат поиска или, если результатов больше одного, заголовок "relevance" и следующие за ним результаты. 
"docid" отображает порядковый номер результата в цепочке. 
"rank" показывает относительную релевантность запроса в данном документе.


# О проекте
Проект разделён на функциональные элементы каждый из которых выполняет свою функцию. 
* converter_JSON.h вмещает в себя класс Converter_JSON,  который отвечает за всю работу с JSON (чтение из "config", "request" и запись в "answers"). 
* inverted_index.h содержит класс InvertedIndex, который занимается чтением текстовых данных из файлов с текстом и присвоением индекса их содержимому в записимости от соответствия запросам. 
* search_server.h содержит класс SearchServer, который проверяет соотвествие запросов и содержимого файлов при помощи подготовленный классом InvertedIndex данных и составляет для них индексы релевантности.
* projects_source.h содержит все подключаемые библиотеки и вспомогательные файлы, включая, описанные выше, а также содержит вспомогательные структуры для классов InvertedIndex и SearchServer.
* exception_source.h содержит все предусмотренные исключения для нештатных ситуаций работы программы.
В проекте была использована библиотека, не содержащаяся в стандартной библиотеке - nlohmann. Она преназначена для работы с JSON и играет ключевую роль в чтении и записи.

# Настройка проекта
Необходимо скачать проект, заполнить все файлы (кроме "answers", конечно), а после запустить программу через компилятор или через терминал (команда актуальна для windows) с помощью команды start endgame и программа внесёт результат в файл.
