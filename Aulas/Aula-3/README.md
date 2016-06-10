O codigo do Programa está em c_helloword.cpp

para compilar o programa use
gcc -o [nome do arquivo de saida]

para compilar em modo de debug use
gcc -g -o  [nome do arquivo de saida]

Já estão criados arquivos de execução sh para facilitar, por exemplo, para compilar em modo release use
./compile.sh

para compilar em modo debug use 
./compiledebug.sh



Tutorial gdb

gdb [arquivo executavel de debug]

já está criado sh para executar o comando direto - para isso use

./debuggdb

pode se usar: 

r =para rodar.
l =listar o codigo
b [linha] =para colocar um breakpoint
n =rodar para proxima linha
step =para entrar em metodo
info breakpoint =mostra os breakpoints
delete [numero] =deleta o breakpoint [numero]
p [variaveis] =mostra o valor da variavel [variavel]
where =mostra qual metodo esta sendo usado
quit =sai do gdb
