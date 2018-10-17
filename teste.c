#include <stdio.h>
#include <pthread.h>
void preencher();
void emitir();
void comprar();
void poltronas();

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int i;
int j;
int cont = 1;
char ingressos[30];

int main(){
	preencher();
    pthread_t emissor, comprador1, comprador2;
    pthread_create(&emissor, 0, emitir, NULL);
    pthread_create(&comprador1, 0, comprar, '2');
    pthread_create(&comprador2, 0, comprar, '3');
    printf("antes");
    pthread_join(comprador1, 0);
    pthread_join(comprador2, 0);
	printf("depois");
	poltronas();
	

}


void comprar(char *t){
	while(cont){
		sleep(1);
		for(i=0; i<30; i++){	
			pthread_mutex_lock(&mutex);
			if(ingressos[i]=='E'){
				printf("\n Comprador: %c - Poltrona: %d\n", t, i);
				ingressos[i] = t;
				j = i;
				i = j;
			}
			else if(ingressos[i] == 'N'){
				printf("Thread %u ainda não existem bilhetes emitidos !\n", (unsigned char) pthread_self());
			}
			if(ingressos[29] != 'E' && ingressos[29] != 'N'){
				printf("Ingressos esgotados !");
			}
			pthread_mutex_unlock(&mutex);
		}
		cont = confere();
	}	
	printf("Thread %u encerrada !", (unsigned char) pthread_self());
	puts("");
	pthread_exit(0);
	
}

int confere(){
	int i;
	for(i=0; i<30; i++){
		if(ingressos[i] == 'E' || ingressos[i] == 'N'){
		return 1;	
		}
	}
	return 0;
}

void emitir(){
	int i;
	for(i=0; i<30; i++){
		if(ingressos[i] == 'N'){
			ingressos[i] = 'E';
			printf("emitido %s \n", ingressos);
			sleep(3);
		}
	}
	printf("thread %u encerrada. \n", (unsigned char) pthread_self());
	pthread_exit(0);
}


void preencher(){
	int i;
	for(i = 0; i<30; i++){
		ingressos[i]='N';
	}
}

void poltronas(){
	int k;
	int thread_1 = 0;
	int thread_2 = 0;
	for(k=0; k<30; k++){
		if(ingressos[k] == '2'){
			thread_1++;
		}
		if(ingressos[k] == '3'){
			thread_2++;
		}
	}
	
	printf("Comprador 1 - %d	||		Comprador 2 - %d\n", thread_1, thread_2);
	puts("");
}


