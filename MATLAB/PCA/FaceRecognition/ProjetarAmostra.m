%Projeta uma nova amostra no espaço das PCs
%Entrada:
%   x = amostra a ser projetada
%   mn = média de cada coluna da matriz de dados
%   s = desvio padrão de cada coluna
%   coef = autovetores
%Saída:
%   y = amostra no novo espaço vetorial
function y = ProjetarAmostra(x,mn,mn2,s,Y)
y = x(:)';
y=y-mn;
y=y-mn2;
y=y./s;
y=y*Y;
end