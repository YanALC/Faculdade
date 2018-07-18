%% Função para ler as imagens e salvar em uma matriz de forma que cada linha seja uma imagem
function z = lerImgs(caminho,ind,treino,reg)
z = zeros(ind*treino,1024*768);
cont=1;
for i = 1:ind
    file = strcat(caminho,'base\');
    filename = strcat(file,int2str(i));
    cd(filename);
    for j=1:treino
        x = im2double(imread(strcat(reg,int2str(j),'.tif')));
        x = x(:)';
        z(cont,:) = x; %Concatena y em z
        cont=cont+1;
        clear x;
    end
end
cd (caminho);%Caminho corrente
end