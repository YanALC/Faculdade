%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%Paulo Renato Baliza Silva%%
%%        04/12/2016       %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%Reeditado%%%%%%%%%%%%%
%%     Ronany Alves        %%
%%     Matheus Nunes       %%
%%  Yan Américo Lobianchi  %%
%%		28/03/2018		   %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
close all;
clc;

    %% Parâmetros
ind=40;
amostras=10;
dim=[112 92];
caminho = 'D:\Google Drive (yanalc2017@gmail.com)\Monitoria\Fundamentos da Computação III\PCA\App\';

%% Análise
op = input('testar(1), análise(2), sair(0): ');
while(op~=0)
    treino = double(input('Treinamento: '));
    [data, testeVet] = lerImgs(caminho,amostras,treino);

    %% PCA
    [Y,projData,varPerc,media,media2,s] = PCA(data);
    % Y=PCs proj
    % Data=dados projetados em Y
    % varPerc=percentual de cada PC
    % demais são parâmetros para normalização de dados
    
    raw = MatrizFotos(data,ind,treino,[112 92]);
    % matriz com as fotos de treino de cada individuo em cada linha
    
    ef = MatrizFotos(Y',ind,treino,[112 92]);
    % matriz com as auto faces de cada individuo em cada linha
    imshowpair(raw(1:5*dim(1),:),ef(1:5*dim(1),:),'montage');
    %%
    %% Classificação KNN
    %Mdl=KNN(projData,ind,treino);
    %%
    switch(op)
        case 1
            im=1;
            while(im)
                im = input('Imagem (ex: ''s8\\5.pgm'')(0 para sair): ');
                if(im==0)
                    break;
                end
                x = im2double(imread(strcat(caminho,'orl_faces\',im)));
                y = ProjetarAmostra(x,media,media2,s,Y);
                id = Identificar(Classificar(projData,y));
                formatSpec = 'Indivíduo reconhecido: %2.2i';
                fprintf(formatSpec,id);
                figure;
                imshowpair(reshape(data(id,:),92,112),x,'montage');
            end
        case 2
            clear data testeVet Y projData media media2 s;
            teste = amostras-treino;
            formatSpec = '\n%2.2i indivíduos\n%2.2i fotos de treinamento\n%2.2i fotos de teste\nNº de componentes principais: %2.2i\nPercentual das 5 primeiras componentes\n1ª componente: %2.2f%% \n2ª componente: %2.2f%% \n3ª componente: %2.2f%% \n4ª componente: %2.2f%% \n5ª componente: %2.2f%% \nTotal: %2.2f%% \n';
            fprintf(formatSpec,ind,treino,teste,length(varPerc),varPerc(1),varPerc(2),varPerc(3),varPerc(4),varPerc(5),sum(varPerc(1:5)));
            perc=zeros(1,20);
            rate=zeros(1,20);
            rate(:)=teste*ind;
            erros=[];
            for o=1:20
            [data, testeVet] = lerImgs(caminho,amostras,treino);
            [Y,projData,varPerc,media,media2,s] = PCA(data);
            d=zeros(1,teste*ind);
            id=zeros(1,teste*ind);
            k=1;
            for i=1:ind
                for j=1:teste
					x = im2double(imread(strcat(caminho,'orl_faces\s',num2str(i),'\',num2str(testeVet(j)),'.pgm')));
					y = ProjetarAmostra(x,media,media2,s,Y);
                    %id(k) = predict(Mdl,y);
                    d(k) = Classificar(projData,y);
                    id(k) = Identificar(d(k),ind,amostras,teste);
                    if id(k)~=i
					   rate(o)=rate(o)-1;
					   erros=[erros;i,j];
                    end
                    k=k+1;
                end
            end
            perc(o)=(double(rate(o))/double(teste*ind))*100.0;
            end
            formatSpec = '\nAcuracia: \nFotos de teste: %2.2i \nFotos de teste reconhecidas: %2.2i~%2.2i \n Percentual médio: %2.2f%% \n Percentual máximo: %2.2f%% \n';
            fprintf(formatSpec,teste*ind,min(rate),max(rate),mean(perc),max(perc));
    end
    op = input('testar(1), análise(2), sair(0): ');
    clear x i j k formatSpec;
end
%%%


