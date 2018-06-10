--CONSULTAS

--Relatório de cada locacao de um automovel por pessoa
select locacoes.cpf, locacoes.nome, locacoes.fatura, locacoes.placa, modelo.descricao as modelo, modelo.marca as marca, categoria.descricao as categoria,
locacoes.kminicio, locacoes.kmfinal, categoria.diaria, locacoes.qtd as "qtd de diarias", categoria.diaria * locacoes.qtd as "valor diarias"
from automovel join (select cliente.cpf as cpf, cliente.nome as nome, locacao.fatura_cod_fatura as fatura, locacao.automovel_placa as placa,
                     locacao.kminicio as kminicio, locacao.kmfinal as kmfinal, locacao.qtddiarias as qtd
from fatura join cliente on fatura.cliente_cpf = cliente.cpf join locacao on fatura.cod_fatura = locacao.fatura_cod_fatura) as locacoes on automovel.placa = locacoes.placa
join modelo on automovel.modelo_id_modelo = modelo.id_modelo
join categoria on automovel.categoria_id_categoria = categoria.id_categoria
order by locacoes.nome;

--Relatório de fatura por pessoa
select relatorio.cpf, relatorio.nome, relatorio.tipo, relatorio.fatura, sum(relatorio.diarias) as "valor total"
from (select locacoes.cpf as cpf, locacoes.nome as nome, locacoes.fatura as fatura, locacoes.tipo as tipo, categoria.diaria * locacoes.qtd as diarias
from automovel 
join (select cliente.cpf as cpf, cliente.nome as nome, cliente.tipo as tipo, locacao.automovel_placa as placa, locacao.fatura_cod_fatura as fatura, locacao.qtddiarias as qtd
      from fatura join cliente on fatura.cliente_cpf = cliente.cpf join locacao on fatura.cod_fatura = locacao.fatura_cod_fatura)
      as locacoes on automovel.placa = locacoes.placa
join categoria on automovel.categoria_id_categoria = categoria.id_categoria) as relatorio
group by relatorio.cpf, relatorio.nome, relatorio.tipo, relatorio.fatura
order by relatorio.nome;
