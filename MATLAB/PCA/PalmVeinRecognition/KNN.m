%% Modelo para Classificação KNN
function Modelo = KNN(data,ind,treino)
label = zeros(1,ind*treino);
for i=1:(ind*treino)
    label(i) = ceil(i/treino);
end
label=label';
Modelo = fitcknn(data,label,'NumNeighbors',treino,'HyperparameterOptimizationOptions',struct('AcquisitionFunctionName','expected-improvement-plus'));
%Modelo = fitcknn(data,label,'OptimizeHyperparameters','auto','HyperparameterOptimizationOptions',struct('AcquisitionFunctionName','expected-improvement-plus'));
%Modelo = fitcknn(data,label,'NumNeighbors',treino,'Distance','cityblock');
end