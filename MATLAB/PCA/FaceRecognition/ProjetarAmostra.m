%Projeta uma nova amostra no espa�o das PCs
%Entrada:
%   x = amostra a ser projetada
%   mn = m�dia de cada coluna da matriz de dados
%   s = desvio padr�o de cada coluna
%   coef = autovetores
%Sa�da:
%   y = amostra no novo espa�o vetorial
function y = ProjetarAmostra(x,mn,mn2,s,Y)
y = x(:)';
y=y-mn;
y=y-mn2;
y=y./s;
y=y*Y;
end