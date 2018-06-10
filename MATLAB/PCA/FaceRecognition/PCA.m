function [Y,PC,varPerc,media,media2,s] = PCA(data)
    data = data';
    [~,N] = size(data); % M = n� linhas (amostras)
	media = mean(data,2)';
    mData = repmat(media',1,(size(data,2)));
    data=data-mData;
    s = std(data,0,2)';
    media2 = mean(data,2)';
    data = normalizar(data')'; % normaliza os dados atrav�s do desvio padr�o
	
%% Matriz de Covari�ncia
	Z = data-repmat(mean(data,2),1,N); %subtrai pela m�dia
	cov = (Z'*Z)/(N-1); %calcula a covari�ncia

	
%% Autovalores e Autovetores
	[v,e] = eig(cov); % v = autovetores ; e = autovalores
	e = diag(e);
    
	[e,idx]  =  sort(e,'descend'); % autovalores em ordem decrescente e armazena os indices
	coef = v(:,idx); % rearranja os autovetores pelos indices dos maiores autovalores
	% coef = coef(:,1:o); % escolhe quantas componentes usar
    % coef = loadings
    
    varPerc(:)=(e(:)/sum(e))*100;
    
%% Y = Novas Componentes (scores)
	Y = data*coef;

%% Proje��o
    PC = data'*Y;
    
clear mData data2;
%data = normalize(data')';
%[~,Y,~,~,varPerc] = pca(data);
end