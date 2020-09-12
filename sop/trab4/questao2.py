file = open("lista-arqs", "r")

arquivos = [["temp", "temp"]]
arquivos.pop()

temp = file.readlines()
for linha in temp:
    arquivos.append(linha.split())


#a) Quantos arquivos foram encontrados?
total = len(arquivos)
print("a) Foram encontrados" , total, "arquivos.")


#b) Qual o maior tamanho de arquivo observado? A que arquivo corresponde?
max = [-1, "nada"]
for linha in arquivos:
    if max[0] < int(linha[1]):
        max[0] = int(linha[1])
        max[1] = linha[0]

arq = max[1].strip('"')
print("b) O maior arquivo eh", arq, "que tem tamanho de", max[0], "bytes.")


#c) Quantos arquivos com tamanho zero existem? A que porcentagem do total eles correspondem?
arquivos_0 = 0
for linha in arquivos:
    if int(linha[1]) == 0:
        arquivos_0 += 1

print("c) Existem", arquivos_0, "arquivos de tamanho 0, que correspondem a {:.3f}% do total.".format(arquivos_0*100/total))


#d) Qual o tamanho medio de arquivo? Qual a porcentagem de arquivos com tamanho igual ou menor do que a media?
media = 0
menores = 0
for linha in arquivos:
    media += int(linha[1])
total_bytes = media
media /= total
media = int(media)

for linha in arquivos:
    if int(linha[1]) <= media:
        menores += 1

print("d) A media de tamanho eh", media, "bytes, com {:.3f}% dos arquivos menores que ela.".format(menores*100/total))


#e) Qual a mediana do tamanho de arquivo?
mediana = 0
vetor_mediana = [0 for x in range(total)]
for i in range(total):
    vetor_mediana[i] = int(arquivos[i][1])
vetor_mediana.sort()

if total%2 == 0:
    mediana = (vetor_mediana[int(total/2)] + vetor_mediana[int(total/2+1)])/2
    mediana = int(mediana)
else:
    mediana = vetor_mediana[int(total/2)]

print("e) A mediana eh ", mediana, " bytes.", sep='')


#f) Qual o menor tamanho de bloco necessário para que pelo menos 50% dos arquivos ocupem apenas um bloco?
# Qual a porcentagem de arquivos que ocuparia um bloco se esse tamanho fosse adotado? 
# Quantos blocos (como tamanho encontrado) ocuparia o maior arquivo?

menor_bloco = 2
while menor_bloco < mediana:
    menor_bloco *= 2

qnt_unico_bloco = 0
for linha in arquivos:
    if int(linha[1]) < menor_bloco:
        qnt_unico_bloco += 1

print("f) O menor tamanho de bloco eh", menor_bloco, "bytes.")
print("\t{:.3f}% dos arquivos ocupariam apenas um bloco.".format(qnt_unico_bloco*100/total))
print("\tO maior arquivo ocuparia", int(max[0]/menor_bloco)+1, "blocos de", menor_bloco, "bytes.")


#g) Sabendo que um i-node no Linux possui 12 ponteiros diretos e indireção simples, dupla e tripla, e supondo
# que os ponteiros de disco (endereços de bloco) sejam de 32 bits, determine:
# a porcentagem de arquivos que não precisam de indireção (i.e., que usam apenas os ponteiros diretos);
# a porcentagem de arquivos que precisam de indireção simples;
# a porcentagem de arquivos que precisam de indireção dupla;
# a porcentagem de arquivos que precisam de indireção tripla.
diretos = 0
i_simples = 0
i_dupla = 0
i_tripla = 0
for x in vetor_mediana:
    if x <= (12*menor_bloco):
        diretos += 1
    elif x <= ((menor_bloco/4)*menor_bloco):
        i_simples += 1
    elif x <= ((menor_bloco/4)*(menor_bloco/4)*menor_bloco):
        i_dupla += 1
    elif x <= ((menor_bloco/4)*(menor_bloco/4)*(menor_bloco/4)*menor_bloco):
        i_tripla += 1

print("g) Ponteiros diretos: {:.3f}%".format(diretos*100/total))
print("\tIndirecao simples: {:.3f}%".format(i_simples*100/total))
print("\tIndirecao dupla: {:.3f}%".format(i_dupla*100/total))
print("\tIndirecao tripla: {:.3f}%".format(i_tripla*100/total))


#h) Considere que o sistema de arquivos aloca um número integral de blocos para cada arquivo. Por exemplo,
# se um arquivo tem 1337 bytes e o tamanho de bloco é de 1 KB, serão alocados dois blocos para esse arquivo,
# o que significa que ele ocupará 2 KB no disco, dos quais 2048 − 1337 = 711 bytes serão desperdiçados
# por fragmentação interna. Sabendo disso, calcule o espaço desperdiçado por fragmentação interna (total e
# porcentagem) considerando os arquivos analisados.
# DICA: você precisará saber o tamanho de bloco usado pelo seu sistema de arquivos. Para isso, use o comando
# stat arq (onde arq é um arquivo contido em /tmp/lista-arqs) e veja o valor de IO Block.
desperdicio = 0
for x in vetor_mediana:
    desperdicio += 4096 - (x%4096)
print("h) O espaco desperdicado por fragmentacao interna eh", desperdicio, "bytes ({:.3f}%).".format(desperdicio*100/total_bytes))


file.close()