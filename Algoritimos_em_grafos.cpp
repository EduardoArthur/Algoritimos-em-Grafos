#include <bits/stdc++.h>
using namespace std;

int Mat[1010][1010], matemp[1010][1010];
int n, tam_f = 0, numv=0, k=0;
vector<vector<int> > F;
int vis[1010], cor[1010];

// Criando Matriz
void Cria_Matriz(int n){
    int x,y;
    memset(Mat,0,sizeof(Mat));
    do{
        cout << "Digite as arestas:" << endl;
        cin >> x >> y;
        cin.clear();
		fflush(stdin);
        if(x > 0 && y > 0 && x <= n && y <= n){
            Mat[x-1][y-1]=1;
            Mat[y-1][x-1]=1;
        }     
    }while(x > 0 || y > 0);
}

//Imprime Matriz
void Print(int M[1010][1010], int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout << M[i][j] << " ";
        }
        cout << endl;
    }
}

//======================================================================
// ARQUIVOS
//======================================================================

//Salva arquivo
void Save_File(int n,int M[1010][1010],string filename){

    fstream myFile;
    myFile.open(filename, fstream::out);

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            myFile << M[i][j] << " ";
        }
        myFile << endl;
    }
    myFile.close();
    
    filename.erase(filename.end()-4, filename.end()); 
    fstream newFile;
    newFile.open("Grafos_salvos.txt", fstream::out | fstream::app);
    newFile << filename << endl;    
    newFile.close();
    
}

//Carrega arquivo
void Read_File(string filename){
    
    char c;
    int tmp;
    vector<int> aux;
    tam_f = 0;n = 0;
    ifstream myFile;
    myFile.open(filename);
    memset(Mat,0,sizeof(Mat));
    memset(cor, -1, sizeof(cor));
    myFile.get(c);
    while(myFile){
        while(c != '\n') {
            if(isdigit(c)){
                tmp = c - 48 ;
                aux.push_back(tmp); 
                tam_f++;
            } 
            myFile.get(c); 
        }
        F.push_back(aux);
        aux.clear();
        myFile.get(c);
    }
    tam_f = sqrt(tam_f);
    for(int i=0; i<tam_f;i++) {
        for(int j=0;j<tam_f;j++) Mat[i][j] = F[i][j];
    }
    F.clear();
    myFile.close();
    n = tam_f;
}

void Exibe_files(){
	
	ifstream myFile;
	myFile.open("Grafos_salvos.txt");
	if (myFile.fail()) {
		cout << "Nenhum Grafo encontrado" << endl;
	}else{
		cout << myFile.rdbuf();
	}
}

void Call_Load(int x){
	
	string Filename;
	
	cout << "Voce ira carregar um grafo salvo" << endl;
	cout << "Lista de Grafos atualmente salvos no sistema" << endl;
	cout << "============================================" << endl;
	Exibe_files();
	cout << "============================================" << endl << endl;
	cout << "ATENCAO COM LETRA MAIUSCULA" << endl;
	
	if(x == 1){
		cout << "Digite o nome do grafo para carregar: " << endl;	
	}else if(x == 2){
		cout << "Digite o nome do grafo para fazer a coloracao: " << endl;	
	}else{
		cout << "Digite o nome do grafo para ver se eh Euleriano: " << endl;
	}
		cin >> Filename;
		Filename = Filename + ".txt";
		Read_File(Filename);
		Print(Mat,n);
	
}

//======================================================================
// CONECTIVIDADE
//======================================================================

// Busca em profundidade
void DFS(int v){
    vis[v] = 1;
    for(int i = 0; i < n; i++){
        if(Mat[v][i]){
            if(!vis[i]){
				DFS(i);
			}
        }
    }
}

// Checar conectividade
int checa_conexo(){
    int comp = 0;
    for(int i = 0; i < n; i++){
        if(!vis[i]){
            DFS(i);
            comp++;
        } 
    }
    memset(vis, 0, sizeof(vis));
    if(comp == 1){
		cout << "Conexo! possui apenas 1 componente conexo" << endl;
		return 1;
	}else{
		cout << "Nao Conexo" << endl;
		cout << "Numero de componentes Conexos: " << comp << endl;
		return comp;
	}
	
}

bool conexo(){
	int comp = 0;
    for(int i = 0; i < n; i++){
        if(!vis[i]){
            DFS(i);
            comp++;
        } 
    }
    memset(vis, 0, sizeof(vis));
    if(comp == 1){
		return true;
	}else{
		return false;
	}
	
}



//======================================================================
// Gerando Grafos especiais
//======================================================================

//======================================================================
// N-Cubo
//======================================================================
void n_cubo(int x){
    int tam_cubo = pow(2,x);
    memset(Mat,0,sizeof(Mat));
    n = tam_cubo;

    if(x==0){
		Mat[0][0] = 0;
	}else if(x==1){
        Mat[0][0]=0;
        Mat[0][1]=1;
        Mat[1][0]=1;
        Mat[1][1]=0;
    }else{
        int p = tam_cubo/2;
        n_cubo(x-1);
        for(int i=0;i<=p;i++){
            for(int j=0;j<=p;j++){
                Mat[i+p][j+p] = Mat[i][j];
            }
        }
        for(int i=0;i<tam_cubo;i++){
			Mat[tam_cubo-i-1][i] = 1;
		}
    }
}

//======================================================================
// Completo
//======================================================================
void Kn(int x){
    memset(Mat,0,sizeof(Mat));
    n = x;
    for(int i=0;i<x;i++){
        for(int j=0;j<x;j++){
            if(i==j){
				Mat[i][j]=0;
			}else{
				Mat[i][j]=1;
			}
        }
    }
}

//======================================================================
// Caminho
//======================================================================
void Pn(int x){
    memset(Mat,0,sizeof(Mat));
    n = x;
    for(int i=0;i<x;i++) {
        if(i != x-1){
			Mat[i][i+1] = 1;
		}
        if(i != 0){
			Mat[i][i-1] = 1;
		}
    }
}

//======================================================================
// Ciclo
//======================================================================
void Cn(int x){
    memset(Mat,0,sizeof(Mat));
    n = x;
    for(int i=0;i<x;i++) {
        if(i>0){
			Mat[i][i-1] = 1;
		}
        if(i!=x-1){
			Mat[i][i+1] = 1;
		}
        if(i==0){
			Mat[i][x-1] = 1;
		} 
        if(i==x-1){
			Mat[i][0] = 1;
		}
    }
}

//======================================================================
// Roda
//======================================================================
void Wn(int x){
    memset(Mat,0,sizeof(Mat));
    n = x+1;
    for(int i=0;i<x;i++) {
        if(i>0){
			Mat[i][i-1] = 1;
		}
        if(i!=x-1){
			Mat[i][i+1] = 1;
		}
        if(i==0){
			Mat[i][x-1] = 1;
		} 
        if(i==x-1){
			Mat[i][0] = 1;
		}
        Mat[x][i] = 1;
        Mat[i][x] = 1;
        Mat[x][x] = 0;
    }
}

//======================================================================
// Bipartido completo
//======================================================================
void Kn1_n2(int x,int y){
    memset(Mat,0,sizeof(Mat));
    int tot=x+y;
    n = tot;
    for(int i=0;i<tot;i++){
        for(int j=0;j<tot;j++){
            if(i!=j){
                if(i<x && j>=x){
					Mat[i][j] = 1;
				}
                if(i>=x && j<x){
					Mat[i][j] = 1;
				}
            }
        }
    }
}

//======================================================================
// Estrela
//======================================================================
void Sn(int y){
    memset(Mat,0,sizeof(Mat));
    int tot=1+y;
    n = tot;
    for(int i=0;i<tot;i++){
        for(int j=0;j<tot;j++){
            if(i!=j){
                if(i<1 && j>=1){
					Mat[i][j] = 1;
				}
                if(i>=1 && j<1){
					Mat[i][j] = 1;
				}
            }
        }
    }
}

//======================================================================
// ESCOLHA DOS GRAFOS
//======================================================================

void gera_Ncubo(){
	int cubo;
	cout << "Digite o valor de n para gerar o N-Cubo(Qn)" << endl;
    cin >> cubo;
    cin.clear();
	fflush(stdin);
    while(cubo < 0){
		cout << "N precisa ser maior ou igual a 0" << endl;
        cout << "Digite o valor de n" << endl;
        cin >> cubo;
        cin.clear();
		fflush(stdin);
    }
    n_cubo(cubo);
    int tam;
    tam = pow(2,cubo);
    Print(Mat,tam);
    string arquivo = "Q" + to_string(cubo) + ".txt"; 
    Save_File(tam,Mat,arquivo);
    cout << "Seu Grafo foi salvo como: " << arquivo << endl;
    cout << "Para Carrega-lo basta selecionar a opcao carregar grafo e buscar por: " << "Q" + to_string(cubo) << endl << endl;
}

void gera_Completo(){
	int k;
	cout << "Digite o valor de n para gerar o Completo(Kn)" << endl;
    cin >> k;
    cin.clear();
	fflush(stdin);
    while(k < 1){
		cout << "n precisa ser maior ou igual a 1" << endl;
        cout << "Digite o valor de n" << endl;
        cin >> k;
        cin.clear();
		fflush(stdin);
    }
    Kn(k);
    Print(Mat,k);
    string arquivo = "K" + to_string(k) + ".txt"; 
    Save_File(k,Mat,arquivo);
    cout << "Seu Grafo foi salvo como: " << arquivo << endl;
    cout << "Para Carrega-lo basta selecionar a opcao carregar grafo e buscar por: " << "K" + to_string(k) << endl << endl;

}

void gera_Caminho(){
	int x;
	cout << "Digite o valor de n para gerar o Caminho(Pn)" << endl;
    cin >> x;
    cin.clear();
	fflush(stdin);
    while(x < 1){
		cout << "n precisa ser maior ou igual a 1" << endl;
        cout << "Digite o valor de n" << endl;
        cin >> x;
        cin.clear();
		fflush(stdin);
    }
    Pn(x);
    Print(Mat,x);
    string arquivo = "P" + to_string(x) + ".txt"; 
    Save_File(x,Mat,arquivo);
    cout << "Seu Grafo foi salvo como: " << arquivo << endl;
    cout << "Para Carrega-lo basta selecionar a opcao carregar grafo e buscar por: " << "P" + to_string(x) << endl << endl;
	
}

void gera_Ciclo(){
	int x;
	cout << "Digite o valor de n para gerar o Ciclo(Cn)" << endl;
    cin >> x;
    cin.clear();
	fflush(stdin);
    while(x < 3){
		cout << "O tamanho precisa ser maior ou igual a 3" << endl;
        cout << "Digite o valor de n" << endl;
        cin >> x;
        cin.clear();
		fflush(stdin);
    }
    Cn(x);
    Print(Mat,x);
    string arquivo = "C" + to_string(x) + ".txt"; 
    Save_File(x,Mat,arquivo);
    cout << "Seu Grafo foi salvo como: " << arquivo << endl;
    cout << "Para Carrega-lo basta selecionar a opcao carregar grafo e buscar por: " << "C" + to_string(x) << endl << endl;
	
}

void gera_Roda(){
	int x;
	cout << "Digite o valor de n para gerar a Roda(Wn)" << endl;
    cin >> x;
    cin.clear();
	fflush(stdin);
    while(x < 3){
		cout << "O tamanho precisa ser maior ou igual a 3" << endl;
        cout << "Digite o valor de n" << endl;
        cin >> x;
        cin.clear();
		fflush(stdin);
    }
    Wn(x);
    Print(Mat,x+1);
    string arquivo = "W" + to_string(x) + ".txt"; 
    Save_File(x+1,Mat,arquivo);
    cout << "Seu Grafo foi salvo como: " << arquivo << endl;
    cout << "Para Carrega-lo basta selecionar a opcao carregar grafo e buscar por: " << "W" + to_string(x) << endl << endl;
	
}

void gera_BipartidoCompleto(){
	int n1 = 0;
	int n2 = 0;
	while(n1<1 || n2<1){
		cout << "Digite o tamanho da parte superior n1" << endl;
		cin >> n1;
		cin.clear();
		fflush(stdin);
		cout << "Digite o tamanho da parte inferior n2" << endl;
		cin >> n2;
		cin.clear();
		fflush(stdin);
		if(n1<1 || n2<1){
			cout << "O tamanho de ambos tem que ser maior ou igual a 1" << endl;
		}	
	}
	Kn1_n2(n1,n2);
	Print(Mat,n1+n2);
    string arquivo = "K" + to_string(n1) + "," + to_string(n2) + ".txt"; 
    Save_File(n1+n2,Mat,arquivo);
    cout << "Seu Grafo foi salvo como: " << arquivo << endl;
    cout << "Para Carrega-lo basta selecionar a opcao carregar grafo e buscar por: " << "K" + to_string(n1) + "," + to_string(n2) << endl << endl;
	
}

void gera_Estrela(){
	int x;
	cout << "Digite o valor de n para gerar a Estrela(Sn)" << endl;
    cin >> x;
    cin.clear();
	fflush(stdin);
    while(x < 1){
		cout << "n precisa ser maior ou igual a 1" << endl;
        cout << "Digite o valor de n" << endl;
        cin >> x;
        cin.clear();
		fflush(stdin);
    }
    Sn(x);
    Print(Mat,x+1);
    string arquivo = "S" + to_string(x) + ".txt"; 
    Save_File(x+1,Mat,arquivo);
    cout << "Seu Grafo foi salvo como: " << arquivo << endl;
    cout << "Para Carrega-lo basta selecionar a opcao carregar grafo e buscar por: " << "S" + to_string(x) << endl << endl;
	
}

void escolha_grafo(){
	int grafo;
	
	do{
		cout << "Escolha o numero referente a opcao desejada" << endl;
		cout << "1 - Gerar Completo(Kn)" << endl;
		cout << "2 - Gerar Bipartido Completo(Kn1,n2)" << endl;
		cout << "3 - Gerar Estrela (Sn)" << endl;
		cout << "4 - Gerar Ciclo(Cn)" << endl;
		cout << "5 - Gerar Roda(Wn)" << endl;
		cout << "6 - Gerar Caminho(Pn)" << endl;
		cout << "7 - Gerar N-Cubo(Qn)" << endl;
		cout << "8 - Voltar" << endl;
		cin >> grafo;
		cin.clear();
		fflush(stdin);	
	}while(grafo < 1 || grafo > 8);
	
	switch(grafo){
		case 1:
			gera_Completo();
			break;
		case 2:
			gera_BipartidoCompleto();
			break;
		case 3:
			gera_Estrela();
			break;
		case 4:
			gera_Ciclo();
			break;
		case 5:
			gera_Roda();
			break;
		case 6:
			gera_Caminho();
			break;
		case 7:
			gera_Ncubo();
			break;
		case 8:
			break;
			
	}
	
}

//======================================================================
// Cria Mycielsky
//======================================================================

void Mycielsky(int w, int num_crom){

    memset(Mat,0,sizeof(Mat));

    if(w == num_crom) {
        for(int i=0;i<w;i++){
            for(int j=0;j<w;j++){
                if(i==j){
					Mat[i][j] = 0;
				}else{
					Mat[i][j] = 1;
				}
            }
        }
        numv = w;
    }else{
        Mycielsky(w,num_crom-1);
        k = numv;
        numv = 2*numv+1;
        
        for(int i=1;i<=k+1;i++){
            for(int j=1;j<=k+1;j++){
                Mat[i+k][j+k] = Mat[i-1][j-1];
                if(j<=k){
					Mat[i+k][j] = Mat[i-1][j-1];
				}
                if(i<=k){
					Mat[i][j+k] = Mat[i-1][j-1];
				}
            }
        }

        for(int i=0;i<numv;i++){
            for(int j=0;j<numv;j++){
                if(i==0 && j<=k){
					Mat[i][j]=1;
				}
                if(i==0 && j>k){
					Mat[i][j]=0;
				}
                if(j==0 && i<=k){
					Mat[i][j]=1;
				}
                if(j==0 && i>k){
					Mat[i][j]=0;
				}
                if((i>0 && i<k+1) && (j>0 && j<k+1)){
					Mat[i][j]=0;
				}
                if(i==j){
					Mat[i][j]=0;
				}
            }
        }

    }
    
    
}

//======================================================================
// Chama Mycielsky
//======================================================================

void Call_Mycielsky(){
    int w=0,num_crom=0;
    bool ok = false;

	do{
		cout << "Digite o valor da clique maxima Omega " << endl;
		cin >> w;
		cin.clear();
		fflush(stdin);
		cout << "Digite o numero cromatico Chi " << endl;
		cin >> num_crom;
		cin.clear();
		fflush(stdin);
		if (w > num_crom) {
            cout << "O numero cromatico Chi tem que ser maior ou igual a Omega" << endl;
        }else{
			ok = true;
			break;
		}
    }while(!ok);
    Mycielsky(w,num_crom);
    string arq = "Mycielsky" + to_string(w) + "," + to_string(num_crom) + ".txt";
	
    
    if(w == num_crom){
		for(int i=0;i<w;i++){
			for(int j=0;j<w;j++){
				matemp[i][j] = Mat[w - 1 -j][w - 1 -i]; 
			}
		}
		for(int i=0;i<w;i++){
			for(int j=0;j<w;j++){
				Mat[i][j] = matemp[i][j]; 
			}
		}
		Print(Mat, w);
		Save_File(w,Mat,arq);
	}else{
		for(int i=0;i<numv;i++){
			for(int j=0;j<numv;j++){
				matemp[i][j] = Mat[numv -1 -j][numv - 1 -i]; 
			}
		}
		for(int i=0;i<numv;i++){
			for(int j=0;j<numv;j++){
				Mat[i][j] = matemp[i][j]; 
			}
		}
		Print(Mat, numv);
		Save_File(numv,Mat,arq);
	}
}

//======================================================================
// Coloracao e metodo Guloso
//======================================================================


int coloring(vector<int> degree) {
    vector<pair<int, int>> degree_sorted;

    for (int i = 0; i < n; i++) {
        degree_sorted.push_back({ degree[i], i });
    }

    sort(degree_sorted.rbegin(), degree_sorted.rend());

    vector<int> color(n), available_colors(n + 1);

    for (int i = 0; i < n; i++) {
        for (int c = 1; c <= n; c++) {
            available_colors[c] = 0;
        }

        for (int j = 0; j < n; j++) {
            if (Mat[degree_sorted[i].second][j] == 1 && color[j] != 0) {
                available_colors[color[j]] = 1;
            }
        }

        for (int c = 1; c <= n; c++) {
            if (available_colors[c] == 0) {
                color[degree_sorted[i].second] = c;
                break;
            }
        }
    }

    int mx_color = 0;

    for (int i = 0; i < n; i++) {
        mx_color = max(mx_color, color[i]);
    }

    return mx_color;
}

int ChamaColoracao(){
	
	vector<int> grau(n);

	
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(Mat[i][j] == 1){
				grau[i]++;
			}
		}
	}
	
	/*  Verificando o grau de cada vertice
	for(int i=0;i<n;i++){
		cout << "Vertice[" << i+1 << "] grau : " << grau[i] << endl;	
	}
	*/
	return coloring(grau);
	
}


//======================================================================
// Verificar se é Euleriano
//======================================================================


bool Euleriano(){
	if(conexo()){
		int cont;
		for(int i=0;i<n;i++){
			cont = 0;
			for(int j=0;j<n;j++){
				if(Mat[i][j] == 1){
					cont++;
				}
			}
			if(cont%2 != 0){
				return false;
			}
		}
		return true;
	}else{
		return false;
	}
	
}

//======================================================================
// MAIN
//======================================================================

int main (void){
	
	int opcao;
	
	bool running = true;
	
	string Filename;
	
	while(running){
		opcao = 0;
		while(opcao < 1 || opcao > 8){
			cout << "Escolha o numero referente a opcao desejada" << endl;
			cout << "1  -  Criar Grafo" << endl;
			cout << "2  -  Carregar Grafo" << endl;
			cout << "3  -  Checar Conectividade" << endl;
			cout << "4  -  Gerar Grafo Especial" << endl;
			cout << "5  -  Coloracao Gulosa" << endl;
			cout << "6  -  Gerar Grafo Mycielsky" << endl;
			cout << "7  -  Verificar se eh Euleriano" << endl;
			cout << "8  -  Encerrar" << endl;
			cin >> opcao;
			cin.clear();
			fflush(stdin);
		}
		switch(opcao){
			
			case 1:
					cout << "Voce ira criar um novo grafo" << endl;
					cout << "Digite o nome do grafo: " << endl;
					cin >> Filename;
					Filename = Filename + ".txt";
					cin.clear();
					fflush(stdin);
					do{
						cout << "Digite o numero de vertices:" << endl;
						cin >> n;
						cin.clear();
						fflush(stdin);
						if(n < 1){
							cout << "O numero de vertices deve ser maior que zero" << endl;
						}
					}while (n < 1);
					Cria_Matriz(n);
					Save_File(n,Mat,Filename);
					cout << endl;
					cout << endl;
					Print(Mat,n);
					
					break;

			case 2: 
					Call_Load(1);
					break;
			case 3:
					checa_conexo();
					break;
			case 4:
					escolha_grafo();
					break;
			case 5:
					Call_Load(2);
					
					cout << endl << "O numero minimo de cores para se pintar o grafo eh " << ChamaColoracao() << " cores" << endl << endl;
						
					break;
			case 6:
					Call_Mycielsky();
					break;
			
			case 7:
					//Call_Load(3);
					if(Euleriano()){
						cout << "Euleriano" << endl;
					}else{
						cout << "Nao Euleriano" << endl;
					}
					break;	
			
			default:
					running = false;
		}
	}

	return 0;

}
