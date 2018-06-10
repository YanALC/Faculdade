function [Y,PC,varPerc,media,media2,s] = PCA(data)
    data = data';
    [~,N] = size(data); % M = nº linhas (amostras)
	media = mean(data,2)';
    mData = repmat(media',1,(size(data,2)));
    data=data-mData;
    s = std(data,0,2)';
    media2 = mean(data,2)';
    data = normalizar(data')'; % normaliza os dados através do desvio padrão
	
%% Matriz de Covariância
	Z = data-repmat(mean(data,2),1,N); %subtrai pela média
	cov = (Z'*Z)/(N-1); %calcula a covariância

	
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

%% Projeção
    PC = data'*Y;
    
clear mData data2;
%data = normalize(data')';
%[~,Y,~,~,varPerc] = pca(data);
end