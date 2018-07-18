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
caminho = '\PCA_FaceRecognition\'; %caminho da aplicação

%% Análise
op = input('testar(1), análise(2), sair(0): ');
while(op~=0)
    treino = double(input('Treinamento: '));
    data = lerImgs(caminho,treino);

    %% PCA
    media = mean(data);
    s = std(data,0,1);
    normData = normalize(data); % normaliza os dados através do desvio padrão
    [Y,coef,varPerc] = PCA(normData');
    projData = normData*Y;
    % Y=PCs de data'
    % projData=dados projetados em Y
    % varPerc=percentual de cada PC
    % demais são parâmetros para normalização de dados
    
    raw = MatrizFotos(data,ind,treino,[112 92]);
    % matriz com as fotos de treino de cada individuo em cada linha
    
    ef = MatrizFotos(Y',ind,treino,[112 92]);
    % matriz com as auto faces de cada individuo em cada linha
    figure(1);
    imshowpair(raw(1:5*dim(1),:),ef(1:5*dim(1),:),'montage');

    %% Análise
    switch(op)
        case 1 %Teste
            im=1;
            while(im)
                im = input('Imagem (ex: ''s8\\5.pgm'')(0 para sair): ');
                if(im==0)
                    break;
                end
                x = im2double(imread(strcat(caminho,'orl_faces\',im)));
                y = ProjetarAmostra(x,media,s,Y);
                id = Identificar(Classificar(projData,y));
                formatSpec = 'Indivíduo reconhecido: %2.2i';
                fprintf(formatSpec,id);
                figure(2);
                imshowpair(reshape(data(id,:),92,112),x,'montage');
            end
        case 2 %Analise Completa
            teste = amostras-treino;
            rate=teste*ind;
            erros=[];
            d=zeros(1,teste*ind);
            id=zeros(1,teste*ind);
            k=1;
            for i=1:ind
                for j=treino+1:amostras
					x = im2double(imread(strcat(caminho,'orl_faces\s',num2str(i),'\',num2str(j),'.pgm')));
					y = ProjetarAmostra(x,media,s,Y);
                    d(k) = Classificar(projData,y);
                    id(k) = Identificar(d(k),ind,amostras,teste);
                    if id(k)~=i
					   rate=rate-1;
                       %fprintf(strcat('\nErrou amostra ',int2str(j),' do indivíduo ',int2str(i)));
					   erros=[erros;i,j];
                    end
                    k=k+1;
                end
            end
            perc=(double(rate)/double(teste*ind))*100.0;
            formatSpec = '\nAcuracia: \nFotos de teste: %2.2i \nFotos de teste reconhecidas: %2.2i \nPercentual de acerto: %2.2f%\n';
            fprintf(formatSpec,teste*ind,rate,perc);
    end
    op = input('\n\ntestar(1), análise(2), sair(0): ');
    clear x i j k formatSpec;
end
%%%


