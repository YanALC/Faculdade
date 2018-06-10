%Função para identificar o indivíduo a partir da distância calculada
%d>(((i-1)*7)+((i-1)*3)) && d<((7*i)+(3*i)+1)
function id = Identificar(d,ind,amostras,teste)
id=1;
for i=1:ind
    if (d+teste*(i-1))>(amostras*(i-1)) && (d+teste*(i-1))<(amostras*i-2)
        id = i;
        break;
    end
end
end