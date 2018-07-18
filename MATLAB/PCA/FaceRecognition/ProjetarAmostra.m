%Projeta uma nova amostra no espaço das PCs
%Entrada:
%   x = amostra a ser projetada
%   media = média de cada coluna da matriz de dados
%   std = desvio padrão de cada coluna
%   coef = autovetores
%Saída:
%   y = amostra no novo espaço vetorial
function y = ProjetarAmostra(x,media,std,Y)
y = x(:)';
y=y-media;
y=y./std;
y=y*Y;
end