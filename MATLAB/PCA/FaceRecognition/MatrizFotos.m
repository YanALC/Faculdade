%% Função para formar uma só imagem de um banco de imagens
function raw = MatrizFotos(mat,ind,num,dim)
raw=zeros(dim(1)*ind,dim(2)*num);
i=0:dim(1):(dim(1)*ind);
j=0:dim(2):(dim(2)*num);
for n=1:ind
    temp1=zeros(dim(1),dim(2)*num);
    for m=1:num
        temp = reshape(mat(m+(n-1)*num,:),dim(1),dim(2));
        temp = histeq(temp,255);
        temp1(:,j(m)+1:j(m+1))=temp;
    end
    raw(i(n)+1:i(n+1),:)=temp1;
end
end
