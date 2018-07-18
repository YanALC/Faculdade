%% Função onde é realizada a PCA dos dados
function [Y,coef,varPerc] = PCA(data)	
%% Matriz de Covariância
M = size(data,1);
Z = data-repmat(mean(data),M,1); %subtrai pela média
cov = (Z'*Z)/(M-1); %calcula a covariância
clear Z;
%% Autovalores e Autovetores
[v,e] = eig(cov); % v = autovetores ; e = autovalores
e = diag(e);
clear cov;
[e,idx]  =  sort(e,'descend'); % autovalores em ordem decrescente e armazena os indices
coef = v(:,idx); % rearranja os autovetores pelos indices dos maiores autovalores
% coef = coef(:,1:o); % escolhe quantas componentes usar
% coef = loadings

varPerc(:)=(e(:)/sum(e))*100;
clear v e;
%% Y = Novas Componentes (scores)
Y = data*coef;

clear mData data ;
end