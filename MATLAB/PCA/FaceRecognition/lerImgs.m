function [z,teste] = lerImgs(caminho,amostras,treino)
ind=40;
z = zeros(40*treino,92*112);
cont=1;
teste=zeros(1,amostras-treino);
idx=1;
n = randperm(treino,treino);
for i = 1:amostras
    if isempty(find(n==i,1))
        teste(idx)=i;
        idx=idx+1;
    end
end
for i = 1:ind
    file = strcat(caminho,'orl_faces\s');
    filename = strcat(file,int2str(i));
    cd(filename);
    for j=1:treino
        x = im2double(imread(strcat(int2str(n(j)),'.pgm')));
        y = x(:)';
        z(cont,:) = y; %Concatena y em z
        cont=cont+1;
    end
end
clear x y;
cd (caminho);%Caminho corrente
end