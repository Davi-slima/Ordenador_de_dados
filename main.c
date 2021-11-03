#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <time.h>
#define MAX 100000

void quickSort(int *number, int first, int last) {
	int i, j, pivot, temp;
	
	i = first;
	j = last;
	pivot = number[(first + last) / 2];
	
	while (i <= j) {
		while (number[i] < pivot && i < last) {
			i++;
		}
		while (number[j] > pivot && j > first) {
			j--;
		}
		if (i <= j) {
			temp = number[i];
			number[i] = number[j];
			number[j] = temp;
			i++;
			j--;
		}
	}
	
	if (j > first) {
		quickSort(number, first, j);
	}
	if (i < last) {
		quickSort(number, i, last);
	}
}

void intercalation(int p, int q, int r, int v[]) {
	int i, j, k;
	int vet[MAX];
	
	i = p;
	j = q;
	k = 0;
	
	while (i < q && j <= r) {
		if (v[i] <= v[j]) {
			vet[k++] = v[i++];
		}
		vet[k++] = v[j++];
	}
	while (i < q) {
		vet[k++] = v[i++];
	}
	while (j <= r) {
		vet[k++] = v[j++];
	}
	for (i = p; i <= r; i++) {
		v[i] = vet[i - p];
	}
}

void mergeSort(int p, int r, int v[]) {
	if (p < r) {
		int q = (p + r) / 2;
		mergeSort(p, q, v);
		mergeSort(q + 1, r, v);
		intercalation(p, q + 1, r, v);
	}
}

void sieve(int *vet, int raiz, int fundo);

void heapSort(int *vet, int n) {
	int i, tmp;

	for (i = (n / 2); i >= 0; i--) {
		sieve(vet, i, n - 1);
	}

	for (i = n-1; i >= 1; i--) {
		tmp = vet[0];
		vet[0] = vet[i];
		vet[i] = tmp;
		sieve(vet, 0, i-1);
	}
}

void sieve(int *vet, int raiz, int fundo) {
	int pronto, filhoMax, tmp;

	pronto = 0;
	while ((raiz*2 <= fundo) && (!pronto)) {
		if (raiz*2 == fundo) {
			filhoMax = raiz * 2;
		}
		else if (vet[raiz * 2] > vet[raiz * 2 + 1]) {
			filhoMax = raiz * 2;
		}
		else {
			filhoMax = raiz * 2 + 1;
		}

	if (vet[raiz] < vet[filhoMax]) {
		tmp = vet[raiz];
		vet[raiz] = vet[filhoMax];
		vet[filhoMax] = tmp;
		raiz = filhoMax;
    }
	else {
      pronto = 1;
	}
  }
}

int main(){
	setlocale(LC_ALL, "Portuguese");
	system ("color b");

	char line[100], *result;
	int count,quick,merge,heap,choice, archive, value, manual_choice, manual_choice_2, vet_value;
	clock_t t,j,t_merge,j_merge,t_heap,j_heap;
  
  	FILE *in_cinqk = fopen("massa/50k/Sem Duplicidade/Aleatório/dtaleat50kuni6.txt", "rt");
  	FILE *in_decre_cinqk = fopen("massa/50k/Sem Duplicidade/Descrescente/dtdecre50kuni8.txt", "rt");
	FILE *in_cemk = fopen("massa/100k/Sem Duplicidade/Aleatório/dtaleat100kuni6.txt", "rt");
	FILE *in_decre_cemk = fopen("massa/100k/Sem Duplicidade/Descrescente/dtdecre100kuni8.txt", "rt");
	FILE *in_dezk = fopen("massa/10k/Com Duplicidade/Concavo-DecresceCresce/dtconcv10kdup7.txt", "rt");
	FILE *in_dezk_al = fopen("massa/10k/Sem Duplicidade/Aleatório/dtaleat10kuni0.txt", "rt");
	
	if ((in_cinqk == NULL) || (in_decre_cinqk == NULL) || (in_cemk == NULL) || (in_decre_cemk == NULL)) {
		printf("Erro ao tentar abrir arquivo");
	}

	printf("                                                                           \n");
	printf("                      ANÁLISE DE DESEMPENHO DE DADOS                       \n");
	printf("                                                                           \n");
	printf("                                                                           \n");
	printf("       DIGITE 1 - PARA SELECIONAR UM DE NOSSOS ARQUIVOS                    \n");
	printf("       DIGITE 2 - PARA ADICIONAR MANUALMENTE OU GERAR NUMEROS ALEATÓRIOS   \n");
	printf("                                                                           \n");
	printf("                                                                           \n");
	printf("                                                                           \n");
	scanf("%d", &choice);
	
	while ((choice != 1) && (choice != 2)) {
		printf("\nOpção inválida. Tente novamente\n");
		printf("Insira uma opção válida: ");
		choice = getchar();
		scanf("%d", &choice);
	}
	
	if (choice == 1) {
		system("cls");
		printf("											                        \n");
		printf("       1 - ABRIR ARQUIVO DE 50K COM DADOS ALEATÓRIOS                \n");
		printf("       2 - ABRIR ARQUIVO DE 50K COM DADOS EM ORDEM DECRESCENTE      \n");
		printf("       3 - ABRIR ARQUIVO DE 100K COM DADOS ALEATÓRIOS               \n");
		printf("       4 - ABRIR ARQUIVO DE 100K COM DADOS EM ORDEM DECRESCENTE     \n");
		printf("       5 - ABRIR ARQUIVO DE 10K CONCAVO DECRESCENTE CRESCENTE       \n");
		printf("       6 - ABRIR ARQUIVO DE 10K COM DADOS ALEATÓRIOS                \n");
		printf("                                                                    \n");
		scanf("%d", &archive);
		
		while ((archive <= 0) || (archive > 6)) {
	 		printf("Arquivo inválido\nPor favor insira um código que seja válido: ");
	 		archive = getchar();
	 		scanf("%d", &archive);
		}
	}

	if(archive == 1 || archive == 2){
		value = 50000;
	} else if ((archive == 5) || (archive == 6)) {
		value = 10000;
	}
	else {
	 	value = 100000;
	}
 
	int vetor[value],vet[value],v[value];
  
	if(archive == 1){
	  	count = 0;
	 	while (!feof(in_cinqk)){
			result = fgets(line, 100, in_cinqk);
		    if (result){
		   		vetor[count] = atoi(line);
		  		vet[count] = atoi(line);
		  		v[count] = atoi(line);
	      		count++;
			}
	  	}
  		fclose(in_cinqk);
 	} else if (archive == 2) {
	 	count = 0;
	 	while (!feof(in_decre_cinqk)) {
 			result = fgets(line, 100, in_decre_cinqk);
 			if (result) {
 				vetor[count] = atoi(line);
		  		vet[count] = atoi(line);
		  		v[count] = atoi(line);
	      		count++;
			 }
		 }
		 fclose(in_decre_cinqk);
	 } else if (archive == 3){
		count = 0;
  		while (!feof(in_cemk)){
	    	result = fgets(line, 100, in_cemk);
	    	if (result){
	      		vetor[count]=atoi(line);
		  		vet[count]=atoi(line);
		  		v[count]=atoi(line);
	      		count++;
		  	}
  		}
  		fclose(in_cemk);
 	} else if (archive == 4) {
 		count = 0;
 		while (!feof(in_decre_cemk)) {
 			result = fgets(line, 100, in_decre_cemk);
 			if (result) {
 				vetor[count] = atoi(line);
		  		vet[count] = atoi(line);
		  		v[count] = atoi(line);
	      		count++;
			 }
		 }
		 fclose(in_decre_cemk);
	 } else if (archive == 5) {
 		count = 0;
 		while (!feof(in_dezk)) {
 			result = fgets(line, 100, in_dezk);
 			if (result) {
 				vetor[count] = atoi(line);
		  		vet[count] = atoi(line);
		  		v[count] = atoi(line);
	      		count++;
			 }
		 }
		 fclose(in_dezk);
	 } else if (archive == 6) {
 		count = 0;
 		while (!feof(in_dezk_al)) {
 			result = fgets(line, 100, in_dezk_al);
 			if (result) {
 				vetor[count] = atoi(line);
		  		vet[count] = atoi(line);
		  		v[count] = atoi(line);
	      		count++;
			 }
		 }
		 fclose(in_dezk_al);
	 }
	
	if (choice == 2) {
		system("cls");
		printf("											                 \n");
		printf("             1 - INSERIR DADOS DE FORMA NANUAL               \n");
		printf("             2 - GERAR DADOS DE FORMA ALEATÓRIA              \n");
		printf("                                                             \n");
		scanf("%d", &manual_choice);
		
		while ((manual_choice != 1) && (manual_choice != 2)) {
			printf("\nOpção inválida. Tente novamente\n");
			printf("Insira uma opção válida: ");
			manual_choice = getchar();
			scanf("%d", &manual_choice);
		}
	}
	
	if (choice == 2) {
		system("cls");
		printf("													                       \n");
		printf("                           ORDENADOR DE DADOS                              \n");
		printf("													                       \n");
		printf("             Quantos valores você gostaria que fossem armazenados?         \n");
		printf("                          Maximo : 100 mil                          	   \n");
		printf("                                                                           \n");
		printf("                                                                           \n");
		scanf("%d", &manual_choice_2);
		
		while((manual_choice_2 <= 0)|| manual_choice_2 > MAX){
			printf("\n Opção Invalida \n");
			printf(" Digite novamente a opção: \n");
			manual_choice_2 = getchar();
			scanf("%d", &manual_choice_2);	
		}
	}
	
	srand(time(NULL));
	
	if (choice == 2) {
		value = manual_choice_2;
	} 
		
	if (choice == 2) {
		if (manual_choice == 1) {
			for (count = 0; count < value; count++) {
				printf("Insira o %dº valor: ", count + 1);
				scanf("%d", &vet_value);
				vetor[count] = vet_value;
				vet[count] = vet_value;
				v[count] = vet_value;
			}
		}else if (manual_choice == 2) {
			for (count = 0; count < manual_choice_2; count++) {
				vet_value = rand() % MAX;
				vetor[count] = vet_value;
				vet[count] = vet_value;
				v[count] = vet_value;
			}
		}
	}
		
	t = clock();
  	quickSort(vetor, 0, value-1);
  	j = clock()-t;
  
  	t_merge = clock();
  	mergeSort(0, value-1 , vet);
  	j_merge = clock()-t_merge;
  
  	t_heap = clock();
  	heapSort(v, value);
  	j_heap = clock()-t_heap;

	quick = ((double)j)/((CLOCKS_PER_SEC/1000));
	merge = ((double)j_merge)/((CLOCKS_PER_SEC/1000));
	heap = ((double)j_heap)/((CLOCKS_PER_SEC/1000));
	
	if ((quick < merge) && (merge < heap)){
		printf("											  \n");
		printf("**********************************************\n");
		printf("*     |    |    Tempo de execução      |     *\n");
		printf("*     |____|___________________________|     *\n");
		printf("*     | 1º | Quick Sort, Tempo : %d ms |     *\n",quick);
		printf("*     |____|___________________________|     *\n");
		printf("*     | 2º | Merge Sort, Tempo : %d ms |     *\n",merge);
		printf("*     |____|___________________________|     *\n");
		printf("*     | 3º | Heap Sort,  Tempo : %d ms |     *\n",heap);
		printf("*     |____|___________________________|     *\n");
		printf("**********************************************\n");
		printf("											  \n");
		
	}else if ((merge < heap) && (heap < quick)){
	  	printf("											  \n");
		printf("**********************************************\n");
		printf("*     |    |    Tempo de execução      |     *\n");
		printf("*     |____|___________________________|     *\n");
		printf("*     | 1º | Merge Sort, Tempo : %d ms |     *\n",merge);
		printf("*     |____|___________________________|     *\n");
		printf("*     | 2º | Heap Sort,  Tempo : %d ms |     *\n",heap);
		printf("*     |____|___________________________|     *\n");
		printf("*     | 3º | Quick Sort, Tempo : %d ms |     *\n",quick);
		printf("*     |____|___________________________|     *\n");
		printf("**********************************************\n");
		printf("											  \n");
		
	}else if ((heap < merge) && (merge < quick)){
	  	printf("											  \n");
		printf("**********************************************\n");
		printf("*     |    |    Tempo de execução      |     *\n");
		printf("*     |____|___________________________|     *\n");
		printf("*     | 1º |  Heap Sort, Tempo : %d ms |     *\n",heap);
		printf("*     |____|___________________________|     *\n");
		printf("*     | 2º | Merge Sort, Tempo : %d ms |     *\n",merge);
		printf("*     |____|___________________________|     *\n");
		printf("*     | 3º | Quick Sort, Tempo : %d ms |     *\n",quick);
		printf("*     |____|___________________________|     *\n");
		printf("**********************************************\n");
		printf("											  \n");
		
	}else if ((quick < heap) && (heap < merge)){
	  	printf("											  \n");
		printf("**********************************************\n");
		printf("*     |    |    Tempo de execução      |     *\n");
		printf("*     |____|___________________________|     *\n");
		printf("*     | 1º | Quick Sort, Tempo : %d ms |     *\n",quick);
		printf("*     |____|___________________________|     *\n");
		printf("*     | 2º | Heap Sort,  Tempo : %d ms |     *\n",heap);
		printf("*     |____|___________________________|     *\n");
		printf("*     | 3º | Merge Sort, Tempo : %d ms |     *\n",merge);
		printf("*     |____|___________________________|     *\n");
		printf("**********************************************\n");
		printf("											  \n");
		
	}else if ((merge < quick) && (quick < heap)){
	  	printf("											  \n");
		printf("**********************************************\n");
		printf("*     |    |    Tempo de execução      |     *\n");
		printf("*     |____|___________________________|     *\n");
		printf("*     | 1º | Merge Sort, Tempo : %d ms |     *\n",merge);
		printf("*     |____|___________________________|     *\n");
		printf("*     | 2º | Quick Sort, Tempo : %d ms |     *\n",quick);
		printf("*     |____|___________________________|     *\n");
		printf("*     | 3º | Heap Sort,  Tempo : %d ms |     *\n",heap);
		printf("*     |____|___________________________|     *\n");
		printf("**********************************************\n");
		printf("											  \n");
		
	}else {
	  	printf("											  \n");
		printf("**********************************************\n");
		printf("*     |    |    Tempo de execução      |     *\n");
		printf("*     |____|___________________________|     *\n");
		printf("*     | 1º | Heap Sort,  Tempo : %d ms |     *\n",heap);
		printf("*     |____|___________________________|     *\n");
		printf("*     | 2º | Quick Sort, Tempo : %d ms |     *\n",quick);
		printf("*     |____|___________________________|     *\n");
		printf("*     | 1º | Merge Sort, Tempo : %d ms |     *\n",merge);
		printf("*     |____|___________________________|     *\n");
		printf("**********************************************\n");
		printf("											  \n");
  }
  
  	if(value < 5000){
		printf("AVISO: NORMALMENTE PARA QUANTIDADES MENORES QUE 5000, A DIFERENÇA ENTRE OS ORDENADORES É QUASE NULA, SE QUISER VER A DIFERENÇA DE UMA FORMA MAIS CLARA, UTILIZE UM DE NOSSOS ARQUIVOS COM MAIS DE 50 MIL DADOS\n");
	}
	
	printf("													                          \n");
	printf("													                          \n");
	printf("                  Você gostaria de ver os valores ordenados?                  \n");
	printf("													                          \n");
	printf("                            DIGITE 1 - PARA SIM                               \n");
	printf("                   DIGITE QUALQUER OUTRO VALOR - PARA NÃO                     \n");
	printf("                                                                              \n");
	printf("*para melhor visualização a tela se limpara se quiser ver o valores ordenados \n");
	printf("													                          \n");
	scanf("%d", &count);

	if(count == 1){
		system("cls");
			for(count = 0;count < value;count++){
				printf("Posição %d = %d \n",count + 1 ,v[count]);
		 }
	}
  
}
