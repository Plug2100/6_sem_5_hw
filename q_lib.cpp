#include "q_lib.h"
#include "cond.h"









int main(int argc, char **argv) {
    int was_read = 0;
    int test = 0;
    char *input, *output, *test_file;
    unsigned k, n, l;
    complexd *V;
    int box = 0;
    int canon = 0;
    complexd *need;
    complexd *need_new;
    for (int i = 1; i < argc; i++) { 
        string option(argv[i]);
        if(option.compare("Canonization") == 0){
        	canon = 1;
        	n = 2;
        }
        if(option.compare("Black_box") == 0){
        	box = 1;
        }
        if (option.compare("n") == 0) {
            n = atoi(argv[++i]);
        }
        if (option.compare("k") == 0) {
            k = atoi(argv[++i]);
        }
        if (option.compare("l") == 0) {
            l = atoi(argv[++i]);
        }
        if ((option.compare("file_read") == 0)) {
            input = argv[++i];
            was_read = 1;
        }
        if ((option.compare("file_write") == 0)) {
            output = argv[++i];
        }
        if ((option.compare("test") == 0)) {
            test = 1;
        }
        if ((option.compare("file_test") == 0)) {
            test_file = argv[++i];
        }
    }

    MPI_Init(&argc, &argv);
    int rank;
    int size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    unsigned long long index = 1LLU << n;
    unsigned long long seg_size = index / size;
    need = (complexd*) malloc(sizeof(complexd) * seg_size);
    need_new = (complexd*) malloc(sizeof(complexd) * seg_size);
    MPI_Status stat;
    int rc;
    float fr_snd = 0;
    float ans = 0;
    if(box == 1){
    	V = generate_condition(seg_size, rank, size); 
    	NOT(k, V, rank, size, n);
    	for (int i = 0; i < seg_size; i++) {
        	fr_snd += abs(V[i] * V[i]);
        }
        if(rank == 0){
        	ans += fr_snd;
        	for (int i = 1; i < size; i++){
				MPI_Recv(&fr_snd, 1, MPI_DOUBLE, i, 9, MPI_COMM_WORLD, &stat);
				ans += fr_snd;
        	}
        	cout << "NOT " << ans << endl;
        }
        else{
        	rc = MPI_Send(&fr_snd, 1, MPI_DOUBLE, 0, 9, MPI_COMM_WORLD);
        }
        ans = 0;
        fr_snd = 0;
        ROT(k, V, rank, size, n);
    	for (int i = 0; i < seg_size; i++) {
        	fr_snd += abs(V[i] * V[i]);
        }
        if(rank == 0){
        	ans += fr_snd;
        	for (int i = 1; i < size; i++){
				MPI_Recv(&fr_snd, 1, MPI_DOUBLE, i, 9, MPI_COMM_WORLD, &stat);
				ans += fr_snd;
        	}
        	cout << "ROT " << ans << endl;
        }
        else{
        	rc = MPI_Send(&fr_snd, 1, MPI_DOUBLE, 0, 9, MPI_COMM_WORLD);
        }
        ans = 0;
        fr_snd = 0;

        Hadamar(k, V, rank, size, n);
    	for (int i = 0; i < seg_size; i++) {
        	fr_snd += abs(V[i] * V[i]);
        }
        if(rank == 0){
        	ans += fr_snd;
        	for (int i = 1; i < size; i++){
				MPI_Recv(&fr_snd, 1, MPI_DOUBLE, i, 9, MPI_COMM_WORLD, &stat);
				ans += fr_snd;
        	}
        	cout << "Hadamar " << ans << endl;
        }
        else{
        	rc = MPI_Send(&fr_snd, 1, MPI_DOUBLE, 0, 9, MPI_COMM_WORLD);
        }

        ans = 0;
        fr_snd = 0;

        CNOT(k, l, V, rank, size, n);
       // cout << rank << endl << endl;
    //    cout << rank << endl;
    	for (int i = 0; i < seg_size; i++) {
        	fr_snd += abs(V[i] * V[i]);
        }
  //      cout <<fr_snd << ' ' << rank << endl;
      //  cout << "seg_size " << seg_size << endl; 
        if(rank == 0){
        	ans += fr_snd;
        	for (int i = 1; i < size; i++){
				MPI_Recv(&fr_snd, 1, MPI_DOUBLE, i, 9, MPI_COMM_WORLD, &stat);
			//	cout << "res " << i << endl;
				ans += fr_snd;
        	}
        	cout << "CNOT " << ans << endl;
        }
        else{
  //      	cout << "sended" << endl;
        	rc = MPI_Send(&fr_snd, 1, MPI_DOUBLE, 0, 9, MPI_COMM_WORLD);
        }
		

        ans = 0;
        fr_snd = 0;

        CROT(k, l, V, rank, size, n);
       // cout << rank << endl << endl;
    //    cout << rank << endl;
    	for (int i = 0; i < seg_size; i++) {
        	fr_snd += abs(V[i] * V[i]);
        }
  //      cout <<fr_snd << ' ' << rank << endl;
      //  cout << "seg_size " << seg_size << endl; 
        if(rank == 0){
        	ans += fr_snd;
        	for (int i = 1; i < size; i++){
				MPI_Recv(&fr_snd, 1, MPI_DOUBLE, i, 9, MPI_COMM_WORLD, &stat);
			//	cout << "res " << i << endl;
				ans += fr_snd;
        	}
        	cout << "CROT " << ans << endl;
        }
        else{
  //      	cout << "sended" << endl;
        	rc = MPI_Send(&fr_snd, 1, MPI_DOUBLE, 0, 9, MPI_COMM_WORLD);
        }


        ans = 0;
        fr_snd = 0;

        nHadamar(k, l, V, rank, size, n);
    	for (int i = 0; i < seg_size; i++) {
        	fr_snd += abs(V[i] * V[i]);
        } 
        if(rank == 0){
        	ans += fr_snd;
        	for (int i = 1; i < size; i++){
				MPI_Recv(&fr_snd, 1, MPI_DOUBLE, i, 9, MPI_COMM_WORLD, &stat);
			//	cout << "res " << i << endl;
				ans += fr_snd;
        	}
        	cout << "nHadamar " << ans << endl;
        }
        else{
  //      	cout << "sended" << endl;
        	rc = MPI_Send(&fr_snd, 1, MPI_DOUBLE, 0, 9, MPI_COMM_WORLD);
        }


        MPI_Finalize();
    	delete[] V;
    	return 0;
    }
    if(canon == 1){
    	complexd *V = new complexd[seg_size];
    	if(size < 4){
    		if(rank == 0){
    			cout << "Вектор {0,0};{1, 0}" << endl;
    		}
    		if(size == 1){
    			V[0] = {0, 0};
    			V[1] = {1, 0};
    		}
    		else{
    			if(rank == 0){
    				V[0] = {0, 0};
    			}
    			else{
    				V[0] = {1, 0};
    			}
    			//cout << "VVV" << endl;
    		}
    		NOT(1, V, rank, size, 1);
    		if(size == 1){
    			cout << "NOT RESULT " << V[0] << ' ' << V[1] << endl;
    		}
    		else{
    			if(rank == 0){
    				cout << "NOT RESULT " << V[0] << ' ';
        			MPI_Recv(&V[0], 1, MPI_COMPLEX, MPI_ANY_SOURCE, 8, MPI_COMM_WORLD, &stat);
    				cout << V[0] << endl;
    			}
    			else{
    				rc = MPI_Send(&V[0], 1, MPI_COMPLEX, 0, 8, MPI_COMM_WORLD);
    			}
    		}
    		if(size == 1){
    			V[0] = {0, 0};
    			V[1] = {1, 0};
    		}
    		else{
    			if(rank == 0){
    				V[0] = {0, 0};
    			}
    			else{
    				V[0] = {1, 0};
    			}
    		}
    		ROT(1, V, rank, size, 1);
    		if(size == 1){
    			cout << "ROT RESULT " << V[0] << ' ' << V[1] << endl;
    		}
    		else{
				if(rank == 0){
    				cout << "ROT RESULT " << V[0] << ' ';
        			MPI_Recv(&V[0], 1, MPI_COMPLEX, MPI_ANY_SOURCE, 8, MPI_COMM_WORLD, &stat);
    				cout << V[0] << endl;
    			}
    			else{
    				rc = MPI_Send(&V[0], 1, MPI_COMPLEX, 0, 8, MPI_COMM_WORLD);
    			}    		}
    		if(size == 1){
    			V[0] = {0, 0};
    			V[1] = {1, 0};
    		}
    		else{
    			if(rank == 0){
    				V[0] = {0, 0};
    			}
    			else{
    				V[0] = {1, 0};
    			}
    		}
    		Hadamar(1, V, rank, size, 1);
    		if(size == 1){
    			cout << "HADAMAR RESULT " << V[0] << ' ' << V[1] << endl;
    		}
    		else{
				if(rank == 0){
    				cout << "HADAMAR RESULT " << V[0] << ' ';
        			MPI_Recv(&V[0], 1, MPI_COMPLEX, MPI_ANY_SOURCE, 8, MPI_COMM_WORLD, &stat);
    				cout << V[0] << endl;
    			}
    			else{
    				rc = MPI_Send(&V[0], 1, MPI_COMPLEX, 0, 8, MPI_COMM_WORLD);
    			}    		
    		}
    	}

    	if(rank == 0){
    		cout << "Вектор {0,0};{0,0};{0,0};{1,0}" << endl;
    	}
    	if(size == 1){
    		V[0] = {0, 0};
    		V[1] = {0, 0};
    		V[2] = {0, 0};
   			V[3] = {1, 0};
    	}
    	else if (size == 2){
    		if(rank == 0){
    			V[0] = {0, 0};
    			V[1] = {0, 0};
   		}
    		else{
    			V[0] = {0, 0};
    			V[1] = {1, 0};
   			}
    	} else{
    		if(rank != 3){
    			V[0] = {0, 0};
    		} else{
   				V[0] = {1, 0};
   			}
    	}
    	//cout << rank << ' ' << V[0] << ' ' << V[1] << endl;
   		CNOT(1, 2, V, rank, size, 2);
    	if(size == 1){
    		cout << "CNOT RESULT " << V[0] << ' ' << V[1] << ' ' << V[2] << ' ' << V[3] << endl;
   		}
    	else if(size == 2){
    		if(rank == 0){
   				cout << "CNOT RESULT " << V[0] << ' ' << V[1] << ' ';
        		MPI_Recv(&V[0], 1, MPI_COMPLEX, MPI_ANY_SOURCE, 8, MPI_COMM_WORLD, &stat);
    			cout << V[0] << ' ';
    			MPI_Recv(&V[0], 1, MPI_COMPLEX, MPI_ANY_SOURCE, 8, MPI_COMM_WORLD, &stat);
    			cout << V[0] << endl;
   			}
   			else{
    			rc = MPI_Send(&V[0], 1, MPI_COMPLEX, 0, 8, MPI_COMM_WORLD);
    			rc = MPI_Send(&V[1], 1, MPI_COMPLEX, 0, 8, MPI_COMM_WORLD);
    		}
    	} else{
    		if(rank == 0){
    			cout << "CNOT RESULT " << V[0] << ' ';
       			MPI_Recv(&V[0], 1, MPI_COMPLEX, 1, 8, MPI_COMM_WORLD, &stat);
    			cout << V[0] << ' ';
   				MPI_Recv(&V[0], 1, MPI_COMPLEX, 2, 8, MPI_COMM_WORLD, &stat);
    			cout << V[0] << ' ';
    			MPI_Recv(&V[0], 1, MPI_COMPLEX, 3, 8, MPI_COMM_WORLD, &stat);
    			cout << V[0] << endl;
    		} else{
    			rc = MPI_Send(&V[0], 1, MPI_COMPLEX, 0, 8, MPI_COMM_WORLD);
    		}
    	}



    	if(size == 1){
    		V[0] = {0, 0};
    		V[1] = {0, 0};
    		V[2] = {0, 0};
   			V[3] = {1, 0};
    	}
    	else if (size == 2){
    		if(rank == 0){
    			V[0] = {0, 0};
    			V[1] = {0, 0};
   		}
    		else{
    			V[0] = {0, 0};
    			V[1] = {1, 0};
   			}
    	} else{
    		if(rank != 3){
    			V[0] = {0, 0};
    		} else{
   				V[0] = {1, 0};
   			}
    	}
    	//cout << rank << ' ' << V[0] << ' ' << V[1] << endl;
   		CROT(1, 2, V, rank, size, 2);
    	if(size == 1){
    		cout << "CROT RESULT " << V[0] << ' ' << V[1] << ' ' << V[2] << ' ' << V[3] << endl;
   		}
    	else if(size == 2){
    		if(rank == 0){
   				cout << "CROT RESULT " << V[0] << ' ' << V[1] << ' ';
        		MPI_Recv(&V[0], 1, MPI_COMPLEX, MPI_ANY_SOURCE, 8, MPI_COMM_WORLD, &stat);
    			cout << V[0] << ' ';
    			MPI_Recv(&V[0], 1, MPI_COMPLEX, MPI_ANY_SOURCE, 8, MPI_COMM_WORLD, &stat);
    			cout << V[0] << endl;
   			}
   			else{
    			rc = MPI_Send(&V[0], 1, MPI_COMPLEX, 0, 8, MPI_COMM_WORLD);
    			rc = MPI_Send(&V[1], 1, MPI_COMPLEX, 0, 8, MPI_COMM_WORLD);
    		}
    	} else{
    		if(rank == 0){
    			cout << "CROT RESULT " << V[0] << ' ';
       			MPI_Recv(&V[0], 1, MPI_COMPLEX, 1, 8, MPI_COMM_WORLD, &stat);
    			cout << V[0] << ' ';
   				MPI_Recv(&V[0], 1, MPI_COMPLEX, 2, 8, MPI_COMM_WORLD, &stat);
    			cout << V[0] << ' ';
    			MPI_Recv(&V[0], 1, MPI_COMPLEX, 3, 8, MPI_COMM_WORLD, &stat);
    			cout << V[0] << endl;
    		} else{
    			rc = MPI_Send(&V[0], 1, MPI_COMPLEX, 0, 8, MPI_COMM_WORLD);
    		}
    	}


    	if(size == 1){
    		V[0] = {0, 0};
    		V[1] = {0, 0};
    		V[2] = {0, 0};
   			V[3] = {1, 0};
    	}
    	else if (size == 2){
    		if(rank == 0){
    			V[0] = {0, 0};
    			V[1] = {0, 0};
   		}
    		else{
    			V[0] = {0, 0};
    			V[1] = {1, 0};
   			}
    	} else{
    		if(rank != 3){
    			V[0] = {0, 0};
    		} else{
   				V[0] = {1, 0};
   			}
    	}
    	//cout << rank << ' ' << V[0] << ' ' << V[1] << endl;
   		nHadamar(1, 2, V, rank, size, 2);
    	if(size == 1){
    		cout << "nHadamar RESULT " << V[0] << ' ' << V[1] << ' ' << V[2] << ' ' << V[3] << endl;
   		}
    	else if(size == 2){
    		if(rank == 0){
   				cout << "nHadamar RESULT " << V[0] << ' ' << V[1] << ' ';
        		MPI_Recv(&V[0], 1, MPI_COMPLEX, MPI_ANY_SOURCE, 8, MPI_COMM_WORLD, &stat);
    			cout << V[0] << ' ';
    			MPI_Recv(&V[0], 1, MPI_COMPLEX, MPI_ANY_SOURCE, 8, MPI_COMM_WORLD, &stat);
    			cout << V[0] << endl;
   			}
   			else{
    			rc = MPI_Send(&V[0], 1, MPI_COMPLEX, 0, 8, MPI_COMM_WORLD);
    			rc = MPI_Send(&V[1], 1, MPI_COMPLEX, 0, 8, MPI_COMM_WORLD);
    		}
    	} else{
    		if(rank == 0){
    			cout << "nHadamar RESULT " << V[0] << ' ';
       			MPI_Recv(&V[0], 1, MPI_COMPLEX, 1, 8, MPI_COMM_WORLD, &stat);
    			cout << V[0] << ' ';
   				MPI_Recv(&V[0], 1, MPI_COMPLEX, 2, 8, MPI_COMM_WORLD, &stat);
    			cout << V[0] << ' ';
    			MPI_Recv(&V[0], 1, MPI_COMPLEX, 3, 8, MPI_COMM_WORLD, &stat);
    			cout << V[0] << endl;
    		} else{
    			rc = MPI_Send(&V[0], 1, MPI_COMPLEX, 0, 8, MPI_COMM_WORLD);
    		}
    	}

    	MPI_Finalize();
    	delete[] V;
    	return 0;
    }
    
    MPI_Finalize();
    delete[] V;
    delete[] need;
    delete[] need_new;
}