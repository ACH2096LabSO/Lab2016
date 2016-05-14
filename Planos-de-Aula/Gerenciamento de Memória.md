*Matheus Preischadt Pinheiro (8623799)*
*Leonardo Piccioni de Almeida (X)*

# Tema
* Gerenciamento de memória (1)
* Utilização de memória virtual (1)
	* Importância da memória virtual (vantagens e disvantagens) (1)
	* Paginação (1)
	* Endereçamento e tabelas de memória (fake 64bit) (1)
* Gerenciamento de memória no Linux (1, 3, 4 e 5)

# Objetivo
* Apresentar os conceitos bases de gerenciamento de memória a fim de comparar técnicas e apresentar os modelos utilizados no Linux, bem como demonstrar tais técnicas com ferramentas interativas.

# Materias Utilizados
1. Documentação de toda a parte de memória em linux: 
  http://www.tldp.org/LDP/tlk/mm/memory.html
2. Exercício prático, vendo o uso de memória em "tempo real":
  https://access.redhat.com/documentation/en-US/Red_Hat_Enterprise_Linux/5/html/Tuning_an d_Optimizing_Red_Hat_Enterprise_Linux_for_Oracle_9i_and_10g_Databases/chap-Oracle_9i_an d_10g_Tuning_Guide-Memory_Usage_and_Page_Cache.html
3. As estruturas de dados no código do kernel (memória, memblocks, memtypes):
  https://github.com/0xAX/linux-insides/blob/master/mm/linux-mm-1.md
4. Análise do algoritmo de escalonamento (em i1386:):
  http://tldp.org/HOWTO/KernelAnalysis-HOWTO-7.html
5. O algoritmo buddy:
  http://www.memorymanagement.org/mmref/alloc.html#mmref-alloc-buddy
6. Slides
7. Programa Paginação (Java Swing)

# Atividades Práticas ou Demonstrações
* Utilização do "free" (2)
* Software de Paginação (7)

# Momentos da aula
* Conceitos
	* O problema da memória 
	* Por que memória virtual
	* Tipos de paginação
	* Swapping
	* Controles de Acesso
	* Cache
* Implementações/Desenvolvimento Histórico
	* Linux kernel (4 e 5)
* Arquitetura do Sistema
	* Buddy
	* Paginação em Linux
* Prática
	* Demonstração "checking memory usage" (2)
	* Demonstração paginação (7)
