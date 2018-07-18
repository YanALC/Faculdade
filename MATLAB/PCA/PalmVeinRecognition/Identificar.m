%Função para identificar o indivíduo a partir da distância calculada
%d>(((i-1)*7)+((i-1)*3)) && d<((7*i)+(3*i)+1)
%d>(((i-1)*3)+((i-1)*2)) && d<((3*i)+(2*i)+1)
function id = Identificar(d,ind,treino)
id=1;
for i=1:ind
    if (d<=(treino*i)) && (d>=(treino*i-2))
        id = i;
        break;
    end
end
end