function stdData = padronizar(data)
	[M,N] = size(data);
	media = mean(data); % M�dia de cada coluna
	s = std(data); % Desvio Padr�o de cada coluna
	stdData = zeros(M,N);
	for i=1:M
		for j=1:N
			stdData(i,j)=(data(i,j)-media(j))/s(j);
		end
	end
end