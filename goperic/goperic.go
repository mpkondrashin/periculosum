/*
 Copyright (C) 2022 Michael Kondrashin — All Rights Reserved
 You may use, distribute and modify this code under the
 terms of the MIT license.
 You should have received a copy of the MIT license with
 this file. If not, please write to: mkondrashin@gmail.com

 Lates version of this file can be found at following URL:
 https://github.com/mpkondrashin/periculosum

 wrapper.go - example how to use checker
*/

package goperic

import (
	"bufio"
	"errors"
	"fmt"
	"io"
	"os/exec"
)

var ErrUnknownResponse = errors.New("unknown response")

type Periculosum struct {
	cmd    *exec.Cmd
	stdin  io.WriteCloser
	stdout io.ReadCloser
	reader *bufio.Reader
}

func NewPericulosum(path string) (p *Periculosum, err error) {
	p = &Periculosum{}
	p.cmd = exec.Command(path)
	p.stdin, err = p.cmd.StdinPipe()
	if err != nil {
		return nil, err
	}
	p.stdout, err = p.cmd.StdoutPipe()
	if err != nil {
		return nil, err
	}
	err = p.cmd.Start()
	if err != nil {
		return nil, err
	}
	p.reader = bufio.NewReader(p.stdout)
	return p, nil
}

func (p *Periculosum) Close() error {
	_ = p.stdin.Close()
	_ = p.stdout.Close()
	return p.cmd.Process.Kill()
}

func (p *Periculosum) Check(filePath string) (bool, error) {
	p.stdin.Write([]byte(filePath + "\n"))
	//time.Sleep(500 * time.Millisecond)
	line, _, err := p.reader.ReadLine()
	if err != nil {
		return false, err
	}
	switch string(line) {
	case "0":
		return false, nil
	case "1":
		return true, nil
	}
	return false, fmt.Errorf("%s: %w", string(line), ErrUnknownResponse)
}
