-- 1)
explain analyze select mecanico.cpf,mecanico.nome
from mecanico join setor on mecanico.cods = setor.cods
where mecanico.cods > 100 and mecanico.cods < 200;

"Nested Loop  (cost=0.29..415.74 rows=95 width=24) (actual time=0.011..1.245 rows=100 loops=1)"
"  ->  Seq Scan on mecanico  (cost=0.00..267.00 rows=95 width=28) (actual time=0.007..1.137 rows=100 loops=1)"
"        Filter: ((cods > 100) AND (cods < 200))"
"        Rows Removed by Filter: 9900"
"  ->  Index Only Scan using setor_pkey on setor  (cost=0.29..1.57 rows=1 width=4) (actual time=0.001..0.001 rows=1 loops=100)"
"        Index Cond: (cods = mecanico.cods)"
"        Heap Fetches: 0"
"Planning Time: 0.245 ms"
"Execution Time: 1.278 ms"

create index idx_mecanico_setor on mecanico(cods);

"Nested Loop  (cost=5.54..271.90 rows=95 width=24) (actual time=0.049..0.346 rows=100 loops=1)"
"  ->  Bitmap Heap Scan on mecanico  (cost=5.26..123.16 rows=95 width=28) (actual time=0.039..0.136 rows=100 loops=1)"
"        Recheck Cond: ((cods > 100) AND (cods < 200))"
"        Heap Blocks: exact=67"
"        ->  Bitmap Index Scan on idx_mecanico_setor  (cost=0.00..5.24 rows=95 width=0) (actual time=0.023..0.023 rows=100 loops=1)"
"              Index Cond: ((cods > 100) AND (cods < 200))"
"  ->  Index Only Scan using setor_pkey on setor  (cost=0.29..1.57 rows=1 width=4) (actual time=0.002..0.002 rows=1 loops=100)"
"        Index Cond: (cods = mecanico.cods)"
"        Heap Fetches: 0"
"Planning Time: 0.521 ms"
"Execution Time: 0.383 ms"

-- 2)
explain analyze select cpf,nome from mecanico
join conserto on mecanico.codm = conserto.codm
and conserto.data = '13/06/2018';

"Nested Loop  (cost=0.29..419.89 rows=36 width=24) (actual time=0.450..1.699 rows=36 loops=1)"
"  ->  Seq Scan on conserto  (cost=0.00..189.00 rows=36 width=4) (actual time=0.431..1.530 rows=36 loops=1)"
"        Filter: (data = '2018-06-13'::date)"
"        Rows Removed by Filter: 9964"
"  ->  Index Scan using idx_mecanico_codm on mecanico  (cost=0.29..6.41 rows=1 width=28) (actual time=0.004..0.004 rows=1 loops=36)"
"        Index Cond: (codm = conserto.codm)"
"Planning Time: 0.371 ms"
"Execution Time: 1.730 ms"

create index idx_mecanico_setor on mecanico(cods);

"Nested Loop  (cost=0.29..419.89 rows=36 width=24) (actual time=0.065..0.850 rows=36 loops=1)"
"  ->  Seq Scan on conserto  (cost=0.00..189.00 rows=36 width=4) (actual time=0.058..0.752 rows=36 loops=1)"
"        Filter: (data = '2018-06-13'::date)"
"        Rows Removed by Filter: 9964"
"  ->  Index Scan using idx_mecanico_codm on mecanico  (cost=0.29..6.41 rows=1 width=28) (actual time=0.002..0.002 rows=1 loops=36)"
"        Index Cond: (codm = conserto.codm)"
"Planning Time: 0.288 ms"
"Execution Time: 0.868 ms"

-- 3)
explain analyze select mecanico.nome, cliente.nome, conserto.hora
from conserto join mecanico on conserto.codm = mecanico.codm
join veiculo on conserto.codv = veiculo.codv
join cliente on veiculo.codc = cliente.codc;

"Hash Join  (cost=978.00..1220.78 rows=10000 width=31) (actual time=10.139..24.019 rows=10000 loops=1)"
"  Hash Cond: (veiculo.codc = cliente.codc)"
"  ->  Hash Join  (cost=661.00..877.52 rows=10000 width=24) (actual time=6.819..17.369 rows=10000 loops=1)"
"        Hash Cond: (conserto.codv = veiculo.codv)"
"        ->  Hash Join  (cost=342.00..532.26 rows=10000 width=24) (actual time=3.598..8.716 rows=10000 loops=1)"
"              Hash Cond: (conserto.codm = mecanico.codm)"
"              ->  Seq Scan on conserto  (cost=0.00..164.00 rows=10000 width=16) (actual time=0.010..0.898 rows=10000 loops=1)"
"              ->  Hash  (cost=217.00..217.00 rows=10000 width=16) (actual time=3.495..3.498 rows=10000 loops=1)"
"                    Buckets: 16384  Batches: 1  Memory Usage: 632kB"
"                    ->  Seq Scan on mecanico  (cost=0.00..217.00 rows=10000 width=16) (actual time=0.008..1.423 rows=10000 loops=1)"
"        ->  Hash  (cost=194.00..194.00 rows=10000 width=8) (actual time=3.144..3.145 rows=10000 loops=1)"
"              Buckets: 16384  Batches: 1  Memory Usage: 519kB"
"              ->  Seq Scan on veiculo  (cost=0.00..194.00 rows=10000 width=8) (actual time=0.007..1.508 rows=10000 loops=1)"
"  ->  Hash  (cost=192.00..192.00 rows=10000 width=15) (actual time=3.308..3.309 rows=10000 loops=1)"
"        Buckets: 16384  Batches: 1  Memory Usage: 597kB"
"        ->  Seq Scan on cliente  (cost=0.00..192.00 rows=10000 width=15) (actual time=0.008..1.393 rows=10000 loops=1)"
"Planning Time: 0.424 ms"
"Execution Time: 24.367 ms"

create index idx_mecanico_codm on mecanico (codm);
create index idx_veiculo_codv on veiculo (codv);
create index idx_cliente_codc on cliente (codc);

"Hash Join  (cost=978.00..1220.78 rows=10000 width=31) (actual time=8.652..18.811 rows=10000 loops=1)"
"  Hash Cond: (veiculo.codc = cliente.codc)"
"  ->  Hash Join  (cost=661.00..877.52 rows=10000 width=24) (actual time=5.702..12.909 rows=10000 loops=1)"
"        Hash Cond: (conserto.codv = veiculo.codv)"
"        ->  Hash Join  (cost=342.00..532.26 rows=10000 width=24) (actual time=2.926..7.223 rows=10000 loops=1)"
"              Hash Cond: (conserto.codm = mecanico.codm)"
"              ->  Seq Scan on conserto  (cost=0.00..164.00 rows=10000 width=16) (actual time=0.005..0.783 rows=10000 loops=1)"
"              ->  Hash  (cost=217.00..217.00 rows=10000 width=16) (actual time=2.908..2.908 rows=10000 loops=1)"
"                    Buckets: 16384  Batches: 1  Memory Usage: 632kB"
"                    ->  Seq Scan on mecanico  (cost=0.00..217.00 rows=10000 width=16) (actual time=0.004..1.301 rows=10000 loops=1)"
"        ->  Hash  (cost=194.00..194.00 rows=10000 width=8) (actual time=2.763..2.764 rows=10000 loops=1)"
"              Buckets: 16384  Batches: 1  Memory Usage: 519kB"
"              ->  Seq Scan on veiculo  (cost=0.00..194.00 rows=10000 width=8) (actual time=0.005..1.398 rows=10000 loops=1)"
"  ->  Hash  (cost=192.00..192.00 rows=10000 width=15) (actual time=2.937..2.937 rows=10000 loops=1)"
"        Buckets: 16384  Batches: 1  Memory Usage: 597kB"
"        ->  Seq Scan on cliente  (cost=0.00..192.00 rows=10000 width=15) (actual time=0.009..1.230 rows=10000 loops=1)"
"Planning Time: 0.850 ms"
"Execution Time: 19.138 ms"

-- 4)
explain analyze select m.nome, m.funcao, s.cods, s.nome
from setor as s join (select * from mecanico
where nome is not NULL and funcao is not NULL) as m on s.cods = m.codm;

"Nested Loop  (cost=5.54..271.90 rows=95 width=24) (actual time=0.049..0.346 rows=100 loops=1)"
"  ->  Bitmap Heap Scan on mecanico  (cost=5.26..123.16 rows=95 width=28) (actual time=0.039..0.136 rows=100 loops=1)"
"        Recheck Cond: ((cods > 100) AND (cods < 200))"
"        Heap Blocks: exact=67"
"        ->  Bitmap Index Scan on idx_mecanico_setor  (cost=0.00..5.24 rows=95 width=0) (actual time=0.023..0.023 rows=100 loops=1)"
"              Index Cond: ((cods > 100) AND (cods < 200))"
"  ->  Index Only Scan using setor_pkey on setor  (cost=0.29..1.57 rows=1 width=4) (actual time=0.002..0.002 rows=1 loops=100)"
"        Index Cond: (cods = mecanico.cods)"
"        Heap Fetches: 0"
"Planning Time: 0.521 ms"
"Execution Time: 0.383 ms"

create index idx_mecanico_nome_funcao on mecanico (nome,funcao);

"Hash Join  (cost=280.00..523.26 rows=10000 width=35) (actual time=4.504..10.794 rows=10000 loops=1)"
"  Hash Cond: (mecanico.codm = s.cods)"
"  ->  Seq Scan on mecanico  (cost=0.00..217.00 rows=10000 width=26) (actual time=0.013..2.600 rows=10000 loops=1)"
"        Filter: ((nome IS NOT NULL) AND (funcao IS NOT NULL))"
"  ->  Hash  (cost=155.00..155.00 rows=10000 width=13) (actual time=4.446..4.449 rows=10000 loops=1)"
"        Buckets: 16384  Batches: 1  Memory Usage: 577kB"
"        ->  Seq Scan on setor s  (cost=0.00..155.00 rows=10000 width=13) (actual time=0.007..1.475 rows=10000 loops=1)"
"Planning Time: 0.639 ms"
"Execution Time: 11.350 ms"



-- 5)
explain analyze select distinct mecanico.nome, data
from mecanico left join conserto on mecanico.codm = conserto.codm;

"HashAggregate  (cost=582.26..682.26 rows=10000 width=16) (actual time=9.513..11.647 rows=13660 loops=1)"
"  Group Key: mecanico.nome, conserto.data"
"  Batches: 1  Memory Usage: 1425kB"
"  ->  Hash Right Join  (cost=342.00..532.26 rows=10000 width=16) (actual time=3.011..6.129 rows=13682 loops=1)"
"        Hash Cond: (conserto.codm = mecanico.codm)"
"        ->  Seq Scan on conserto  (cost=0.00..164.00 rows=10000 width=8) (actual time=0.004..0.581 rows=10000 loops=1)"
"        ->  Hash  (cost=217.00..217.00 rows=10000 width=16) (actual time=2.940..2.941 rows=10000 loops=1)"
"              Buckets: 16384  Batches: 1  Memory Usage: 632kB"
"              ->  Seq Scan on mecanico  (cost=0.00..217.00 rows=10000 width=16) (actual time=0.007..1.224 rows=10000 loops=1)"
"Planning Time: 0.208 ms"
"Execution Time: 12.306 ms"

create index idx_mecanico_codm_nome on mecanico (codm, nome);

"HashAggregate  (cost=582.26..682.26 rows=10000 width=16) (actual time=9.783..11.281 rows=13660 loops=1)"
"  Group Key: mecanico.nome, conserto.data"
"  Batches: 1  Memory Usage: 1425kB"
"  ->  Hash Right Join  (cost=342.00..532.26 rows=10000 width=16) (actual time=2.674..6.250 rows=13682 loops=1)"
"        Hash Cond: (conserto.codm = mecanico.codm)"
"        ->  Seq Scan on conserto  (cost=0.00..164.00 rows=10000 width=8) (actual time=0.005..0.594 rows=10000 loops=1)"
"        ->  Hash  (cost=217.00..217.00 rows=10000 width=16) (actual time=2.616..2.616 rows=10000 loops=1)"
"              Buckets: 16384  Batches: 1  Memory Usage: 632kB"
"              ->  Seq Scan on mecanico  (cost=0.00..217.00 rows=10000 width=16) (actual time=0.006..1.041 rows=10000 loops=1)"
"Planning Time: 0.297 ms"
"Execution Time: 11.891 ms"

-- 6)
explain analyze select avg(quilometragem)
from veiculo join cliente on veiculo.codc = cliente.codc;

"Aggregate  (cost=562.26..562.27 rows=1 width=8) (actual time=5.307..5.310 rows=1 loops=1)"
"  ->  Hash Join  (cost=317.00..537.26 rows=10000 width=8) (actual time=1.713..4.612 rows=10000 loops=1)"
"        Hash Cond: (veiculo.codc = cliente.codc)"
"        ->  Seq Scan on veiculo  (cost=0.00..194.00 rows=10000 width=12) (actual time=0.004..0.584 rows=10000 loops=1)"
"        ->  Hash  (cost=192.00..192.00 rows=10000 width=4) (actual time=1.698..1.699 rows=10000 loops=1)"
"              Buckets: 16384  Batches: 1  Memory Usage: 480kB"
"              ->  Seq Scan on cliente  (cost=0.00..192.00 rows=10000 width=4) (actual time=0.003..0.765 rows=10000 loops=1)"
"Planning Time: 0.131 ms"
"Execution Time: 5.338 ms"

create index idx_veiculo_codc on veiculo (codc);

"Aggregate  (cost=562.26..562.27 rows=1 width=8) (actual time=5.896..5.898 rows=1 loops=1)"
"  ->  Hash Join  (cost=317.00..537.26 rows=10000 width=8) (actual time=1.759..5.254 rows=10000 loops=1)"
"        Hash Cond: (veiculo.codc = cliente.codc)"
"        ->  Seq Scan on veiculo  (cost=0.00..194.00 rows=10000 width=12) (actual time=0.004..0.617 rows=10000 loops=1)"
"        ->  Hash  (cost=192.00..192.00 rows=10000 width=4) (actual time=1.741..1.742 rows=10000 loops=1)"
"              Buckets: 16384  Batches: 1  Memory Usage: 480kB"
"              ->  Seq Scan on cliente  (cost=0.00..192.00 rows=10000 width=4) (actual time=0.003..0.820 rows=10000 loops=1)"
"Planning Time: 0.261 ms"
"Execution Time: 5.924 ms"

-- 7)
explain analyze select sum(quilometragem) from veiculo group by codc;

"HashAggregate  (cost=244.00..307.08 rows=6308 width=12) (actual time=4.345..5.586 rows=6308 loops=1)"
"  Group Key: codc"
"  Batches: 1  Memory Usage: 721kB"
"  ->  Seq Scan on veiculo  (cost=0.00..194.00 rows=10000 width=12) (actual time=0.007..0.871 rows=10000 loops=1)"
"Planning Time: 0.074 ms"
"Execution Time: 5.912 ms"

create index idx_veiculo_cidade on veiculo(codc);

"HashAggregate  (cost=244.00..307.08 rows=6308 width=12) (actual time=3.375..4.266 rows=6308 loops=1)"
"  Group Key: codc"
"  Batches: 1  Memory Usage: 721kB"
"  ->  Seq Scan on veiculo  (cost=0.00..194.00 rows=10000 width=12) (actual time=0.005..0.678 rows=10000 loops=1)"
"Planning Time: 0.251 ms"
"Execution Time: 4.532 ms"

-- 8)
explain analyze select nome, count (*) from mecanico join conserto on mecanico.codm = conserto.codm 
and data between '12/06/2018' and '19/10/2018' 
group by (mecanico.nome);

"HashAggregate  (cost=585.72..624.70 rows=3898 width=20) (actual time=5.801..6.256 rows=3210 loops=1)"
"  Group Key: mecanico.nome"
"  Batches: 1  Memory Usage: 465kB"
"  ->  Hash Join  (cost=342.00..566.23 rows=3898 width=12) (actual time=2.711..4.693 rows=3884 loops=1)"
"        Hash Cond: (conserto.codm = mecanico.codm)"
"        ->  Seq Scan on conserto  (cost=0.00..214.00 rows=3898 width=4) (actual time=0.009..0.919 rows=3884 loops=1)"
"              Filter: ((data >= '2018-06-12'::date) AND (data <= '2018-10-19'::date))"
"              Rows Removed by Filter: 6116"
"        ->  Hash  (cost=217.00..217.00 rows=10000 width=16) (actual time=2.690..2.691 rows=10000 loops=1)"
"              Buckets: 16384  Batches: 1  Memory Usage: 632kB"
"              ->  Seq Scan on mecanico  (cost=0.00..217.00 rows=10000 width=16) (actual time=0.003..1.145 rows=10000 loops=1)"
"Planning Time: 0.241 ms"
"Execution Time: 6.376 ms"

create index idx_mecanico_nome on mecanico(codm, nome);

"HashAggregate  (cost=585.72..624.70 rows=3898 width=20) (actual time=8.599..9.460 rows=3210 loops=1)"
"  Group Key: mecanico.nome"
"  Batches: 1  Memory Usage: 465kB"
"  ->  Hash Join  (cost=342.00..566.23 rows=3898 width=12) (actual time=4.126..6.986 rows=3884 loops=1)"
"        Hash Cond: (conserto.codm = mecanico.codm)"
"        ->  Seq Scan on conserto  (cost=0.00..214.00 rows=3898 width=4) (actual time=0.011..1.596 rows=3884 loops=1)"
"              Filter: ((data >= '2018-06-12'::date) AND (data <= '2018-10-19'::date))"
"              Rows Removed by Filter: 6116"
"        ->  Hash  (cost=217.00..217.00 rows=10000 width=16) (actual time=4.097..4.098 rows=10000 loops=1)"
"              Buckets: 16384  Batches: 1  Memory Usage: 632kB"
"              ->  Seq Scan on mecanico  (cost=0.00..217.00 rows=10000 width=16) (actual time=0.006..1.756 rows=10000 loops=1)"
"Planning Time: 0.535 ms"
"Execution Time: 9.684 ms"

-- 9)
explain analyze select veiculo.marca, count(conserto.codv) from conserto, veiculo
where conserto.codv = veiculo.codv group by veiculo.marca;

"HashAggregate  (cost=559.26..559.30 rows=4 width=11) (actual time=6.499..6.502 rows=4 loops=1)"
"  Group Key: veiculo.marca"
"  Batches: 1  Memory Usage: 24kB"
"  ->  Hash Join  (cost=319.00..509.26 rows=10000 width=7) (actual time=2.160..4.983 rows=10000 loops=1)"
"        Hash Cond: (conserto.codv = veiculo.codv)"
"        ->  Seq Scan on conserto  (cost=0.00..164.00 rows=10000 width=4) (actual time=0.004..0.578 rows=10000 loops=1)"
"        ->  Hash  (cost=194.00..194.00 rows=10000 width=7) (actual time=2.146..2.147 rows=10000 loops=1)"
"              Buckets: 16384  Batches: 1  Memory Usage: 539kB"
"              ->  Seq Scan on veiculo  (cost=0.00..194.00 rows=10000 width=7) (actual time=0.004..1.068 rows=10000 loops=1)"
"Planning Time: 0.163 ms"
"Execution Time: 6.543 ms"

create index idx_veiculo_codv on veiculo (codv);

"HashAggregate  (cost=559.26..559.30 rows=4 width=11) (actual time=9.132..9.138 rows=4 loops=1)"
"  Group Key: veiculo.marca"
"  Batches: 1  Memory Usage: 24kB"
"  ->  Hash Join  (cost=319.00..509.26 rows=10000 width=7) (actual time=2.939..6.954 rows=10000 loops=1)"
"        Hash Cond: (conserto.codv = veiculo.codv)"
"        ->  Seq Scan on conserto  (cost=0.00..164.00 rows=10000 width=4) (actual time=0.006..0.833 rows=10000 loops=1)"
"        ->  Hash  (cost=194.00..194.00 rows=10000 width=7) (actual time=2.919..2.921 rows=10000 loops=1)"
"              Buckets: 16384  Batches: 1  Memory Usage: 539kB"
"              ->  Seq Scan on veiculo  (cost=0.00..194.00 rows=10000 width=7) (actual time=0.005..1.349 rows=10000 loops=1)"
"Planning Time: 0.301 ms"
"Execution Time: 9.180 ms"

-- 10)
explain analyze select modelo, marca, ano from veiculo
where quilometragem > (select avg(quilometragem) from veiculo join cliente on veiculo.codc = cliente.codc);

"Seq Scan on veiculo  (cost=562.27..781.27 rows=3333 width=12) (actual time=7.170..8.596 rows=4955 loops=1)"
"  Filter: (quilometragem > $0)"
"  Rows Removed by Filter: 5045"
"  InitPlan 1 (returns $0)"
"    ->  Aggregate  (cost=562.26..562.27 rows=1 width=8) (actual time=7.159..7.161 rows=1 loops=1)"
"          ->  Hash Join  (cost=317.00..537.26 rows=10000 width=8) (actual time=2.332..6.313 rows=10000 loops=1)"
"                Hash Cond: (veiculo_1.codc = cliente.codc)"
"                ->  Seq Scan on veiculo veiculo_1  (cost=0.00..194.00 rows=10000 width=12) (actual time=0.002..0.816 rows=10000 loops=1)"
"                ->  Hash  (cost=192.00..192.00 rows=10000 width=4) (actual time=2.316..2.317 rows=10000 loops=1)"
"                      Buckets: 16384  Batches: 1  Memory Usage: 480kB"
"                      ->  Seq Scan on cliente  (cost=0.00..192.00 rows=10000 width=4) (actual time=0.004..1.038 rows=10000 loops=1)"
"Planning Time: 0.261 ms"
"Execution Time: 8.799 ms"

create index idx_veiculo_quilometragem on veiculo (quilometragem);

"Bitmap Heap Scan on veiculo  (cost=628.39..764.05 rows=3333 width=12) (actual time=15.543..16.889 rows=4955 loops=1)"
"  Recheck Cond: (quilometragem > $0)"
"  Heap Blocks: exact=94"
"  InitPlan 1 (returns $0)"
"    ->  Aggregate  (cost=562.26..562.27 rows=1 width=8) (actual time=14.960..14.963 rows=1 loops=1)"
"          ->  Hash Join  (cost=317.00..537.26 rows=10000 width=8) (actual time=4.376..13.761 rows=10000 loops=1)"
"                Hash Cond: (veiculo_1.codc = cliente.codc)"
"                ->  Seq Scan on veiculo veiculo_1  (cost=0.00..194.00 rows=10000 width=12) (actual time=0.006..1.210 rows=10000 loops=1)"
"                ->  Hash  (cost=192.00..192.00 rows=10000 width=4) (actual time=4.351..4.352 rows=10000 loops=1)"
"                      Buckets: 16384  Batches: 1  Memory Usage: 480kB"
"                      ->  Seq Scan on cliente  (cost=0.00..192.00 rows=10000 width=4) (actual time=0.006..2.305 rows=10000 loops=1)"
"  ->  Bitmap Index Scan on idx_veiculo_quilometragem  (cost=0.00..65.28 rows=3333 width=0) (actual time=15.515..15.515 rows=4955 loops=1)"
"        Index Cond: (quilometragem > $0)"
"Planning Time: 0.561 ms"
"Execution Time: 17.194 ms"

-- 11)