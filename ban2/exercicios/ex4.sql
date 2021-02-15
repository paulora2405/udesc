--1
select nome, endereco from cliente

--2
select nome, funcao 
from mecanico
where cods = 2

--3
select nome, cpf from mecanico 
intersect 
select nome, cpf from cliente

--4
select endereco from mecanico
union
select endereco from cliente

--5
select distinct marca
from veiculo, cliente
where veiculo.codc = cliente.codc and cidade = 'Joinville'

--6
select distinct funcao from mecanico

--7
select * from cliente where idade > 25

--8
select cpf, mecanico.nome from mecanico, setor
where setor.nome = 'mecânica' and setor.cods = mecanico.cods

--9
select cpf, nome from mecanico, conserto
where mecanico.codm = conserto.codm and data = '13/06/2014'

--10
select cliente.nome as Nome_cliente, modelo, mecanico.nome as Nome_mecanico, funcao
from cliente join veiculo on cliente.codc = veiculo.codc
join conserto on conserto.codv = veiculo.codv
join mecanico on mecanico.codm = conserto.codm

--11
select mecanico.nome as nome_m, cliente.nome as nome_c, hora
from conserto join mecanico on conserto.codm = mecanico.codm and data = '19/06/2014'
join veiculo on veiculo.codv = conserto.codv
join cliente on cliente.codc = veiculo.codc

--12
select setor.cods, setor.nome
from conserto join mecanico on conserto.codm = mecanico.codm 
and data in('12/06/2014', '14/06/2014')
join setor on setor.cods = mecanico.cods