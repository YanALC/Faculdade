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
% Direita: 02_R_N_H_BH_ / 04_R_N_H_P_ / 06_R_N_L_BH_ / 08_R_N_L_P_ / 09_R_N_L_W_
% Esquerda: 12_L_N_H_BH_ / 14_L_N_H_P_ / 16_L_N_L_BH_ / 18_L_N_L_P_ / 19_L_N_L_W_
ind=56; %qtd de individuos
amostras=5; %qtd de amostras por foto
dim=[768 1024]; %dimensão das imagens
caminho = 'PalmVeinRecognition'; %caminho da aplicação
treino=3; %qtd de amostras para treino

%% Análise
op = input('testar(1), análise(2), sair(0): ');
while(op~=0)
    reg = char(input('Região: '));
    %treino = double(input('Treinamento: '));
    data = lerImgs(caminho,ind,treino,reg);

    %% PCA
    media = mean(data);
    s = std(normData,0,1);
    normData=normalize(normData); %normaliza os dados através do desvio padrão
    [Y,coef,varPerc] = PCA(normData');
    projData = normData*Y;
    % Y=PCs de data'
    % projData=dados projetados em Y
    % varPerc=percentual de cada PC
    % demais são parâmetros para normalização de dados
    
    %% Classificação com KNN com cluster de 3 vizinhos e distância euclidiana
    Mdl=KNN(projData,ind,treino);
    
    %% Análise
    switch(op)
        case 1 %Teste
            im=1;
            while(im)
                im = input('Imagem (ex: ''27\\02_R_N_H_BH_4.tif'')(0 para sair): ');
                if(im==0)
                    break;
                end
                x = im2double(imread(strcat(caminho,'base\',im)));
                y = ProjetarAmostra(x,media,s,Y);
                id = Identificar(Classificar(projData,y));
                formatSpec = 'Indivíduo reconhecido: %2.2i';
                fprintf(formatSpec,id);
                figure(1);
                imshowpair(reshape(data(id,:),dim),x,'montage');
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
					x = im2double(imread(strcat(caminho,'base\',num2str(i),'\',reg,num2str(j),'.tif')));
					y = ProjetarAmostra(x,media,s,Y);
                    %d(k) = Classificar(projData,y);
                    %id(k) = Identificar(d(k),ind,amostras,teste);
					id(k) = predict(Mdl,y);
                    if id(k)~=i
					   rate=rate-1;
                       %fprintf(strcat('\nErrou amostra ',int2str(j),' do indivíduo ',int2str(i)));
					   %erros=[erros;i,j];
                    end
                    k=k+1;
                end
            end
            perc=(double(rate)/double(teste*ind))*100.0;
            %formatSpec = '\nFotos de teste: %2.2i \nFotos de teste reconhecidas: %2.2i \nPercentual de acerto: %2.2f%\n';
            %fprintf(formatSpec,teste*ind,rate,perc);
            formatSpec = 'Fotos de teste reconhecidas: %2.2i \nPercentual de acerto: %2.2f%\n';
            fprintf(formatSpec,rate,perc);
    end
    op = input('\n\ntestar(1), análise(2), sair(0): ');
    clear x i j k formatSpec;
end