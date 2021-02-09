--1
select cpf, nome from mecanico
where cods in (1, 2)

--2
select cpf, nome from mecanico
where cods in (select cods from setor where nome in ('Funilaria', 'Pintura'))

--3 
select cpf, nome from mecanico inner join conserto
using (codm)
where conserto.data = '13/06/2014'

--4
select mecanico.nome as nome_mec, cliente.nome as nome_cli, hora
from mecanico inner join conserto using (codm) inner join veiculo using (codv) inner join cliente using (codc)
where data = '12/06/2014'

--5
select mecanico.nome as nome_mec, funcao, setor.nome as nome_set, setor.cods
from mecanico left join setor using (cods)

--6
select distinct mecanico.nome, conserto.data
from mecanico join conserto using (codm)

--7
select avg(quilometragem)
from veiculo

--8
select sum(quilometragem)
from veiculo, cliente
where veiculo.codc = cliente.codc
group by cidade

--9
select count(*)
from conserto, mecanico
where conserto.codm = mecanico.codm and data between '12/06/2014' and '19/06/2014'
group by nome

--10
select count(*) 
from conserto, veiculo
where conserto.codv = veiculo.codv
group by marca

--11
select modelo, marca, ano
from veiculo
where quilometragem > (
select avg(quilometragem) from veiculo)


--12
select mecanico.nome,data
from mecanico,conserto
where mecanico.codm=conserto.codm
group by (nome,data) having count(mecanico.nome)>1