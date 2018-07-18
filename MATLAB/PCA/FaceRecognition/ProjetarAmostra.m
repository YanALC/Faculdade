%Projeta uma nova amostra no espa�o das PCs
%Entrada:
%   x = amostra a ser projetada
%   media = m�dia de cada coluna da matriz de dados
%   std = desvio padr�o de cada coluna
%   coef = autovetores
%Sa�da:
%   y = amostra no novo espa�o vetorial
function y = ProjetarAmostra(x,media,std,Y)
y = x(:)';
y=y-media;
y=y./std;
y=y*Y;
end