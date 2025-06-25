class Processo:
    def __init__(self, id, tempo_chegada, tempo_execucao_total, prioridade=0):
        self.id = id
        self.tempo_chegada = tempo_chegada
        self.tempo_execucao_total = tempo_execucao_total
        self.tempo_restante = tempo_execucao_total
        self.tempo_conclusao = None
        self.tempo_retorno = None  # tempo_conclusao - tempo_chegada
        self.tempo_espera = None  # tempo sem executar após chegar
        self.primeira_execucao = None

def simular_sjf_preemptivo(processos, quantum=None):
    # Cria cópias dos processos para não modificar os originais
    processos = [Processo(p.id, p.tempo_chegada, p.tempo_execucao_total) for p in processos]
    
    tempo_atual = 0
    processos_concluidos = 0
    total_processos = len(processos)
    timeline = []
    
    # Ordena processos por tempo de chegada
    processos.sort(key=lambda p: p.tempo_chegada)
    
    while processos_concluidos < total_processos:
        # Encontra processos disponíveis no momento atual
        disponiveis = [p for p in processos if p.tempo_chegada <= tempo_atual and p.tempo_restante > 0]
        
        if not disponiveis:
            # Avança o tempo até o próximo processo chegar
            proximos = [p for p in processos if p.tempo_chegada > tempo_atual and p.tempo_restante > 0]
            if proximos:
                tempo_atual = min(p.tempo_chegada for p in proximos)
                continue
            else:
                break  # Não há mais processos para executar
        
        # Escolhe o processo com menor tempo restante
        processo_atual = min(disponiveis, key=lambda p: p.tempo_restante)
        
        # Registra primeira execução
        if processo_atual.primeira_execucao is None:
            processo_atual.primeira_execucao = tempo_atual
        
        # Adiciona na timeline
        inicio_execucao = tempo_atual
        
        # Executa até terminar ou até um processo com menor tempo chegar
        while processo_atual.tempo_restante > 0:
            tempo_atual += 1
            processo_atual.tempo_restante -= 1
            
            # Verifica se chegou algum processo com menor tempo restante
            novos_disponiveis = [p for p in processos if p.tempo_chegada == tempo_atual and p.tempo_restante > 0]
            if novos_disponiveis:
                if min(novos_disponiveis, key=lambda p: p.tempo_restante).tempo_restante < processo_atual.tempo_restante:
                    break
                    
            if processo_atual.tempo_restante == 0:
                break
        
        # Registra na timeline
        timeline.append((processo_atual.id, inicio_execucao, tempo_atual))
        
        # Se o processo terminou, atualiza estatísticas
        if processo_atual.tempo_restante == 0:
            processo_atual.tempo_conclusao = tempo_atual
            processo_atual.tempo_retorno = processo_atual.tempo_conclusao - processo_atual.tempo_chegada
            processo_atual.tempo_espera = processo_atual.tempo_retorno - processo_atual.tempo_execucao_total
            processos_concluidos += 1
    
    return processos, timeline

def simular_round_robin(processos, quantum=5):
    # Cria cópias dos processos para não modificar os originais
    processos = [Processo(p.id, p.tempo_chegada, p.tempo_execucao_total) for p in processos]
    
    tempo_atual = 0
    processos_concluidos = 0
    total_processos = len(processos)
    fila = []
    timeline = []
    
    # Ordena processos por tempo de chegada
    processos.sort(key=lambda p: p.tempo_chegada)
    
    while processos_concluidos < total_processos:
        # Adiciona processos que chegaram à fila
        chegaram = [p for p in processos if p.tempo_chegada <= tempo_atual and 
                   p.tempo_restante > 0 and p not in fila]
        fila.extend(chegaram)
        
        if not fila:
            # Avança o tempo até o próximo processo chegar
            proximos = [p for p in processos if p.tempo_chegada > tempo_atual and p.tempo_restante > 0]
            if proximos:
                tempo_atual = min(p.tempo_chegada for p in proximos)
                continue
            else:
                break  # Não há mais processos para executar
        
        # Pega o próximo processo da fila
        processo_atual = fila.pop(0)
        
        # Registra primeira execução
        if processo_atual.primeira_execucao is None:
            processo_atual.primeira_execucao = tempo_atual
        
        # Adiciona na timeline
        inicio_execucao = tempo_atual
        
        # Executa pelo quantum ou até terminar
        tempo_executado = min(quantum, processo_atual.tempo_restante)
        tempo_atual += tempo_executado
        processo_atual.tempo_restante -= tempo_executado
        
        # Registra na timeline
        timeline.append((processo_atual.id, inicio_execucao, tempo_atual))
        
        # Adiciona processos que chegaram durante esta execução
        chegaram = [p for p in processos if p.tempo_chegada > inicio_execucao and 
                   p.tempo_chegada <= tempo_atual and 
                   p.tempo_restante > 0 and p not in fila]
        fila.extend(chegaram)
        
        # Se o processo ainda não terminou, coloca no final da fila
        if processo_atual.tempo_restante > 0:
            fila.append(processo_atual)
        else:
            # Processo terminou, atualiza estatísticas
            processo_atual.tempo_conclusao = tempo_atual
            processo_atual.tempo_retorno = processo_atual.tempo_conclusao - processo_atual.tempo_chegada
            processo_atual.tempo_espera = processo_atual.tempo_retorno - processo_atual.tempo_execucao_total
            processos_concluidos += 1
    
    return processos, timeline

def formatar_timeline(timeline):
    resultado = "LINHA DO TEMPO\n\n|"
    for processo, inicio, fim in timeline:
        resultado += f"{inicio}|−−−−−{processo}−−−−−|{fim}|"
    return resultado

def main():
    # Tenta abrir o arquivo de entrada
    try:
        nome_arquivo = input("Digite o nome do arquivo de entrada (ou pressione Enter para usar entrada.txt): ") or "entrada.txt"
        with open(nome_arquivo, 'r') as arquivo:
            linhas = arquivo.readlines()
    except FileNotFoundError:
        try:
            with open("input.txt", 'r') as arquivo:
                linhas = arquivo.readlines()
            print("Usando arquivo: input.txt")
        except FileNotFoundError:
            print("Nenhum arquivo de entrada encontrado (tentou entrada.txt e input.txt).")
            return

    # Processa os dados de entrada
    processos_ids = []
    tempos_execucao = []
    tempos_chegada = []
    prioridades = []
    
    for linha in linhas:
        partes = linha.strip().split()
        if not partes:
            continue
            
        if partes[0] == "Processo":
            processos_ids = partes[1:]
        elif partes[0] == "Tempo":
            tempos_execucao = list(map(int, partes[1:]))
        elif partes[0] == "Chegada":
            tempos_chegada = list(map(int, partes[1:]))
        elif partes[0] == "Prioridade":
            prioridades = list(map(int, partes[1:]))
    
    # Cria os processos
    processos = []
    for i in range(len(processos_ids)):
        prioridade = prioridades[i] if i < len(prioridades) else 0
        processos.append(Processo(processos_ids[i], tempos_chegada[i], tempos_execucao[i], prioridade))
    
    # Define o quantum para Round Robin
    quantum = 5
    
    # Pergunta qual algoritmo usar
    print("Escolha o algoritmo de escalonamento:")
    print("1. SJF Preemptivo")
    print("2. Round Robin (quantum = 5)")
    escolha = input("Digite o número correspondente (1 ou 2): ")
    
    if escolha == "1":
        print("\nUsando algoritmo: SJF Preemptivo")
        processos_resultantes, timeline = simular_sjf_preemptivo(processos)
    else:
        print("\nUsando algoritmo: Round Robin")
        print(f"Quantum: {quantum}")
        processos_resultantes, timeline = simular_round_robin(processos, quantum)
    
    # Imprime os resultados
    print("\nProcessos na Fila:")
    print(" ".join(p.id for p in processos_resultantes))
    
    print("\nTempo de CPU requerida pelos processos:")
    print(" ".join(str(p.tempo_execucao_total) for p in processos_resultantes))
    
    print("\nTempo de Chegada dos processos:")
    print(" ".join(str(p.tempo_chegada) for p in processos_resultantes))
    
    print("\n" + formatar_timeline(timeline))
    
    print("\nTempo de Espera de cada processo:")
    print(" ".join(p.id for p in processos_resultantes))
    print(" ".join(str(p.tempo_espera) for p in processos_resultantes))
    
    print("\nTempo de Resposta de cada processo:")
    print(" ".join(p.id for p in processos_resultantes))
    print(" ".join(str(p.tempo_retorno) for p in processos_resultantes))
    
    tempo_medio_resposta = sum(p.tempo_retorno for p in processos_resultantes) / len(processos_resultantes)
    tempo_medio_espera = sum(p.tempo_espera for p in processos_resultantes) / len(processos_resultantes)
    
    print(f"\nTempo Médio de Resposta: {tempo_medio_resposta:.2f}")
    print(f"\nTempo Médio de Espera: {tempo_medio_espera:.2f}")

if __name__ == "__main__":
    main()