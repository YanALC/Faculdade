%Função para identificar o indivíduo a partir da distância calculada
function id = Identificar(d,ind,amostras,teste)
id=1;
for i=1:ind
    if (d+teste*(i-1))>(amostras*(i-1)) && (d+teste*(i-1))<(amostras*i-2)
        id = i;
        break;
    end
end
end