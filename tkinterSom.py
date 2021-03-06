#!/usr/bin/env python3
#-*- coding: utf-8 -*-

import subprocess

from tkinter import *
from tkinter import filedialog

class Packing:
    def __init__( self, objeto_Tk ):
        objeto_Tk.title( "SOM" )

        self.frLocProg = Frame( objeto_Tk )
        self.frLocProg.pack()
        Label( self.frLocProg, text = 'programa em:', fg = 'darkblue', height = 3 ).pack( side = LEFT )
        self.entryLocProg = Entry( self.frLocProg, width = 120 )
        self.entryLocProg.insert( END, '/home/lucas/Documentos/SOM/Programas/SOM_v5.0' )
        self.entryLocProg.pack( side = LEFT )
        self.btLocProg = Button( self.frLocProg, text = 'procura', command = self.prssBtProg )
        self.btLocProg.pack( side = LEFT )

        self.frConfigFormaSOM = Frame( objeto_Tk )
        self.frConfigFormaSOM.pack()
        Label( self.frConfigFormaSOM, text = 'núm.linhas SOM:', fg = 'darkblue', height = 3 ).pack( side = LEFT )
        self.entryNumLinhasSOM = Entry( self.frConfigFormaSOM, width = 4 )
        self.entryNumLinhasSOM.pack( side = LEFT )

        Label( self.frConfigFormaSOM, text = 'núm.colunas SOM:', fg = 'darkblue', height = 3 ).pack( side = LEFT )
        self.entryNumColunasSOM = Entry( self.frConfigFormaSOM, width = 4 )
        self.entryNumColunasSOM.pack( side = LEFT )

        Label( self.frConfigFormaSOM, text = 'núm.componentes nos vetores:', fg = 'darkblue', height = 3 ).pack( side = LEFT )
        self.entryNumComponVet = Entry( self.frConfigFormaSOM, width = 4 )
        self.entryNumComponVet.pack( side = LEFT )

        self.btSortNeurInic = Button( self.frConfigFormaSOM, text = 'sorteia neurônios iniciais' )
        self.btSortNeurInic.bind( "<Button-1>", self.prssBtSortNeurInic )
        self.btSortNeurInic.pack( side = LEFT )

        self.frNomeArqVetInic = Frame( objeto_Tk );
        self.frNomeArqVetInic.pack();
        Label( self.frNomeArqVetInic, text = "arq. vetores iniciais:", fg = 'darkblue', height = 3 ).pack( side = LEFT )
        self.entryNomeArqVetInic = Entry( self.frNomeArqVetInic, width = 120 )
        self.entryNomeArqVetInic.insert( END, 'neurInicSOM.ascii' )
        self.entryNomeArqVetInic.pack( side = LEFT )
        self.btNomeArqVetInic = Button( self.frNomeArqVetInic, text = 'procura', command = self.prssBtArqVetInic )
        self.btNomeArqVetInic.pack( side = LEFT )

        self.frNomeArqVetEntr = Frame( objeto_Tk );
        self.frNomeArqVetEntr.pack();
        Label( self.frNomeArqVetEntr, text = "arq. vetores de entrada:", fg = 'darkblue', height = 3 ).pack( side = LEFT )
        self.entryNomeArqVetEntr = Entry( self.frNomeArqVetEntr, width = 120 )
        self.entryNomeArqVetEntr.pack( side = LEFT )
        self.btNomeArqVetEntr = Button( self.frNomeArqVetEntr, text = 'procura', command = self.prssBtArqVetEntr )
        self.btNomeArqVetEntr.pack( side = LEFT )

        self.frNomeArqRotEntr = Frame( objeto_Tk );
        self.frNomeArqRotEntr.pack();
        Label( self.frNomeArqRotEntr, text = "arq. rótulos de entrada:", fg = 'darkblue', height = 3 ).pack( side = LEFT )
        self.entryNomeArqRotEntr = Entry( self.frNomeArqRotEntr, width = 120 )
        self.entryNomeArqRotEntr.pack( side = LEFT )
        self.btNomeArqRotEntr = Button( self.frNomeArqRotEntr, text = 'procura', command = self.prssBtArqRotEntr )
        self.btNomeArqRotEntr.pack( side = LEFT )

        self.frNumEpocasSOM = Frame( objeto_Tk )
        self.frNumEpocasSOM.pack()

        Label( self.frNumEpocasSOM, text = 'núm.entradas por época:', fg = 'darkblue', height = 3 ).pack( side = LEFT )
        self.entryNumEntrPorEpoca = Entry( self.frNumEpocasSOM, width = 6 )
        self.entryNumEntrPorEpoca.pack( side = LEFT )

        Label( self.frNumEpocasSOM, text = 'núm.aplicações (épocas) arq. entrada:', fg = 'darkblue', height = 3 ).pack( side = LEFT )
        self.entryNumAplicEntradas = Entry( self.frNumEpocasSOM, width = 6 )
        self.entryNumAplicEntradas.pack( side = LEFT )

        self.frRadios = Frame( objeto_Tk )
        self.frRadios.pack()
        Label( self.frRadios, text = 'tipo de distância:', fg = 'darkblue', height = 3 ).pack( side = LEFT )
        self.varBtTipoDistSOM = StringVar()
        self.rdBtTipoDistSOM = Radiobutton( self.frRadios, text = "Euclides", variable = self.varBtTipoDistSOM, value = "Euclid", indicatoron = 0 )
        self.rdBtTipoDistSOM.pack( side = LEFT )
        self.rdBtTipoDistSOM.select()
        self.rdBtTipoDistSOM = Radiobutton( self.frRadios, text = "Manhattan", variable = self.varBtTipoDistSOM, value = "Manhat", indicatoron = 0 )
        self.rdBtTipoDistSOM.pack( side = LEFT )

        Label( self.frRadios, text = 'SOM com atualização (sim para treino)?', fg = 'darkblue', height = 3 ).pack( side = LEFT )
        self.varBtAtualizaSOM = StringVar()
        self.radioBt = Radiobutton( self.frRadios, text = "sim", variable = self.varBtAtualizaSOM, value = "sim", indicatoron = 0 )
        self.radioBt.pack( side = LEFT )
        self.radioBt = Radiobutton( self.frRadios, text = "não", variable = self.varBtAtualizaSOM, value = "nao", indicatoron = 0 )
        self.radioBt.pack( side = LEFT )

        Label( self.frRadios, text = 'Gera figuras de neurônios vencedores?', fg = 'darkblue', height = 3 ).pack( side = LEFT )
        self.varBtSeGeraFigVenc = StringVar()
        self.radioBt = Radiobutton( self.frRadios, text = "sim", variable = self.varBtSeGeraFigVenc, value = "sim", indicatoron = 0 )
        self.radioBt.pack( side = LEFT )
        self.radioBt = Radiobutton( self.frRadios, text = "não", variable = self.varBtSeGeraFigVenc, value = "nao", indicatoron = 0 )
        self.radioBt.pack( side = LEFT )

        self.frAlfaSigmaSOM = Frame( objeto_Tk )
        self.frAlfaSigmaSOM.pack()

        self.frAlfaInicSOM = Frame( self.frAlfaSigmaSOM )
        self.frAlfaInicSOM.pack( side = LEFT )
        Label( self.frAlfaInicSOM, text = 'alfa inic.:', fg = 'darkblue', height = 3 ).pack( side = LEFT )
        self.entryAlfaInicSOM = Entry( self.frAlfaInicSOM, width = 6 )
        self.entryAlfaInicSOM.insert( END, 0.1 )
        self.entryAlfaInicSOM.pack( side = LEFT )

        self.frAlfaFinalSOM = Frame( self.frAlfaSigmaSOM )
        self.frAlfaFinalSOM.pack( side = LEFT )
        Label( self.frAlfaFinalSOM, text = 'alfa final:', fg = 'darkblue', height = 3 ).pack( side = LEFT )
        self.entryAlfaFinalSOM = Entry( self.frAlfaFinalSOM, width = 6 )
        self.entryAlfaFinalSOM.insert( END, 0.01 )
        self.entryAlfaFinalSOM.pack( side = LEFT )

        self.frSigmaInicSOM = Frame( self.frAlfaSigmaSOM )
        self.frSigmaInicSOM.pack( side = LEFT )
        Label( self.frSigmaInicSOM, text = 'sigma inic.:', fg = 'darkblue', height = 3 ).pack( side = LEFT )
        self.entrySigmaInicSOM = Entry( self.frSigmaInicSOM, width = 6 )
        self.entrySigmaInicSOM.insert( END, 15 )
        self.entrySigmaInicSOM.pack( side = LEFT )

        self.frSigmaFinalSOM = Frame( self.frAlfaSigmaSOM )
        self.frSigmaFinalSOM.pack( side = LEFT )
        Label( self.frSigmaFinalSOM, text = 'sigma final:', fg = 'darkblue', height = 3 ).pack( side = LEFT )
        self.entrySigmaFinalSOM = Entry( self.frSigmaFinalSOM, width = 6 )
        self.entrySigmaFinalSOM.insert( END, 1 )
        self.entrySigmaFinalSOM.pack( side = LEFT )

        self.frNomeArqNeurFinSOM = Frame( objeto_Tk )
        self.frNomeArqNeurFinSOM.pack()
        Label( self.frNomeArqNeurFinSOM, text = "arq.neurônios finais:", fg = 'darkblue', height = 3 ).pack( side = LEFT )
        self.entryNomeArqNeurFinSOM = Entry( self.frNomeArqNeurFinSOM, width = 120 )
        self.entryNomeArqNeurFinSOM.insert( END, "neurFinaisSOM.ascii" )
        self.entryNomeArqNeurFinSOM.pack( side = LEFT )

        self.frNomeArqSeqVencedores = Frame( objeto_Tk )
        self.frNomeArqSeqVencedores.pack()
        Label( self.frNomeArqSeqVencedores, text = "arq.seq.neurônios vencedores:", fg = 'darkblue', height = 3 ).pack( side = LEFT )
        self.entryNomeArqSeqVencedores = Entry( self.frNomeArqSeqVencedores, width = 120 )
        self.entryNomeArqSeqVencedores.insert( END, "neurVencedores.ascii" )
        self.entryNomeArqSeqVencedores.pack( side = LEFT )

        self.frNomeArqCoordVencedores = Frame( objeto_Tk )
        self.frNomeArqCoordVencedores.pack()
        Label( self.frNomeArqCoordVencedores, text = "arq.coordenadas neurônios vencedores:", fg = 'darkblue', height = 3 ).pack( side = LEFT )
        self.entryNomeArqCoordVencedores = Entry( self.frNomeArqCoordVencedores, width = 120 )
        self.entryNomeArqCoordVencedores.insert( END, "coordVencedores.ascii" )
        self.entryNomeArqCoordVencedores.pack( side = LEFT )

        self.frExecutaSOM = Frame( objeto_Tk )
        self.frExecutaSOM.pack()
        self.btExecutaSOM = Button( self.frExecutaSOM, text = 'executa SOM' )
        self.btExecutaSOM.bind( "<Button-1>", self.prssBtExecutaSOM )
        self.btExecutaSOM.pack( side = LEFT )

        self.frBtSai = Frame( objeto_Tk )
        self.frBtSai.pack()
        self.btSai = Button( self.frBtSai, text = 'sai', command = quit )
        self.btSai.pack( side = RIGHT )

    def prssBtProg( self ):
        self.strNomeDir = filedialog.askdirectory()
        self.entryLocProg.delete( 0, END )
        self.entryLocProg.insert( 0, self.strNomeDir )

    def prssBtSortNeurInic( self, event ):
        subprocess.call( [ self.entryLocProg.get() + "/sorteiaValInicSOM.m", self.entryNumLinhasSOM.get(), self.entryNumColunasSOM.get(), self.entryNumComponVet.get(), "neurInicSOM.ascii" ] )

    def prssBtArqVetInic( self ):
        self.strNomeArqVetInic = filedialog.askopenfilename( filetypes = [ ( 'ascii', '*.ascii' ), ( 'txt', '*.txt' ) ] )
        self.entryNomeArqVetInic.delete( 0, END )
        self.entryNomeArqVetInic.insert( 0, self.strNomeArqVetInic )

    def prssBtArqVetEntr( self ):
        self.strNomeArqVetEntr = filedialog.askopenfilename( filetypes = [ ( 'ascii', '*.ascii' ), ( 'txt', '*.txt' ) ] )
        self.entryNomeArqVetEntr.delete( 0, END )
        self.entryNomeArqVetEntr.insert( 0, self.strNomeArqVetEntr )

    def prssBtArqRotEntr( self ):
        self.strNomeArqRotEntr = filedialog.askopenfilename( filetypes = [ ( 'ascii', '*.ascii' ), ( 'txt', '*.txt' ) ] )
        self.entryNomeArqRotEntr.delete( 0, END )
        self.entryNomeArqRotEntr.insert( 0, self.strNomeArqRotEntr )

    def prssBtExecutaSOM( self, event ):
        subprocess.call( [ self.entryLocProg.get() + "/som", "-i", self.entryNomeArqVetInic.get(), "-e", self.entryNomeArqVetEntr.get(), "-r", self.entryNomeArqRotEntr.get(), "-l", self.entryNumLinhasSOM.get(), "-c", self.entryNumEntrPorEpoca.get(), "-b", self.entryAlfaInicSOM.get(), "-f", self.entryAlfaFinalSOM.get(), "-s", self.entrySigmaInicSOM.get(), "-g", self.entrySigmaFinalSOM.get(), "-d", self.varBtTipoDistSOM.get(), "-n", self.entryNomeArqNeurFinSOM.get(), "-z", self.varBtAtualizaSOM.get(), "-u", self.varBtSeGeraFigVenc.get(), "-q", self.entryNomeArqSeqVencedores.get(), "-o", self.entryNomeArqCoordVencedores.get(), "-a", self.entryNumAplicEntradas.get() ] )

raiz = Tk()
Packing( raiz )
raiz.mainloop()
