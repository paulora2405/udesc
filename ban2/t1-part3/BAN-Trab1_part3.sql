-- Inserir na DB
insert into banda (id_banda, nome)
values (1, 'ac/dc'),(2, 'djavan'),(3,'planet hemp')

insert into endereco (id_endereco, rua, num, cidade, cep, telefone)
values (1, 'artur', '32', 'jaragua', '8925', '33705696'),
  (2, 'geovanela', '35', 'jaragua', '8441', '33701280')

insert into produtor (id_produtor, nome)
values (1, 'papatinho')

insert into musico (num_registro, nome, id_endereco)
values (1, 'gustavo black alien', 2)

insert into disco (id_disco, titulo, formato, data, id_produtor, num_registro, id_banda)
values (1, 'babylon by gus - o ano do macaco', 'vinil', '12-09-2020', 1, 1, 3)

insert into musica (id_musica, nome, formato, num_registro, id_banda)
values (2, 'caminhos do destino', 'vinil', 1, 3),
  (1, 'mister niteroi', 1, 3),
  (4, 'u - informe', 1, 3),
  (3, 'babylon by gus', 'vinil', 1, 3),
  (5, 'como eu te quero', 'vinil', 1, 3)

insert into musica_disco (id_musica, id_disco)
values (2, 1),
  (1, 1),
  (4, 1)

-- 1) Gatilho para impedir que uma banda seja inserida se já houver outra banda com o mesmo nome
-- ou atualizada com um nome já existente

create or replace function verificaNomeBanda() returns trigger as
$$
begin
	if (select count(nome) from banda where nome = new.nome) > 0
	then
		raise exception 'Já existe uma banda com este nome';
	end if;
	return new;
end;
$$
language plpgsql;

create trigger verificaNomeBanda before insert or update on banda
  for each row execute procedure verificaNomeBanda();


-- 2) Gatilho para impedir que um endereço seja inserido ou atualizado com um telefone já existente

create or replace function verificaTelefone() returns trigger as
$$
begin
  if (select count(telefone) from endereco where telefone = new.telefone) > 0
  then
    raise exception 'Este telefone já pertence a uma residência';
  end if;
  return new;
end;
$$
language plpgsql;

create trigger verificaTelefone before insert or update on endereco
  for each row execute procedure verificaTelefone();


-- 3) Gatilho para impedir que um disco possua mais que 12 musicas no total

create or replace function verificaQuantMusicas() returns trigger as
$$
begin
  if (select count(id_disco) from musica_disco where id_disco = new.id_disco) > 12
  then
    raise exception 'Um disco pode ter no máximo 12 músicas';
  end if;
  return new;
end;
$$
language plpgsql;

create trigger verificaQuantMusicas before insert or update on musica_disco
  for each row execute procedure verificaQuantMusicas();

-- 4) Gatihlo para impedir a inserção ou atualização de produtor com um nome já existente

create or replace function verificaNomeProdutor() returns trigger as
$$
begin
  if (select count(nome) from produtor where nome = new.nome) > 0
  then
    raise exception 'Produtor já existe';
  end if;
  return new;
end;
$$
language plpgsql;

create trigger verificaNomeProdutor before insert or update on produtor
  for each row execute procedure verificaNomeProdutor();