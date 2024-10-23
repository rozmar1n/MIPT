#include"assembler.h"

void MakeMachCode(const char* ProgramFile, const char* cmdFile, const char* logFile)
{      
    FILE* machFile = fopen(logFile, "w");
    if (machFile == 0)
    {
        fprintf(stderr, "We couldn't open you logFile!!!\n");
        return;
    }
    
    FILE* asmFile = fopen(ProgramFile, "r");
    if (asmFile == 0)
    {
        fprintf(stderr, "We couldn't open your asmFile!!!\n");
        return;
    }

    fprintf(machFile, "%s\n", signature);
    
    char signa[] = {82, 79, 83, 84};


    fprintf(machFile, "%d\n", ass_version);

    long int txt_sizeptr = ftell(machFile);

    double* cmd_array = (double*)calloc(1024, sizeof(double));
    int cmd_counter = 0;

    for (int i = 0; i < 2*sizeof(unsigned int); i++)
    {
        fprintf(machFile, "0");
    }
    fprintf(machFile, "\n");

    char cmd[128];
    int err = 1;
    u_int32_t nComands = 0;

//TODO: хэдер под  команды
//TODO: вынести массив структур с командами (instruction).


    while (err)
    {
        err = fscanf(asmFile, "%s", cmd);//TODO: check 10 symbols //fgets or make buffer for full code 

        if (strcmp(cmd, "push") == 0)
        {
            if(err) err = fscanf(asmFile, "%s", cmd);
            if(cmd[1] == 'x')
            {
                double reg = 0;

                if(err) err = fprintf(machFile, "%d ", _cmd_pushr);
                
                cmd_array[cmd_counter] = _cmd_pushr;
                cmd_counter++;

                if (cmd[0] == 'a')
                {
                    fprintf(machFile, "%d ", ax);
                    
                    cmd_array[cmd_counter] = ax;
                    cmd_counter++;
                    
                    continue;
                }
                if (cmd[0] == 'b')
                {
                    fprintf(machFile, "%d ", bx);
                    cmd_array[cmd_counter] = bx;
                    cmd_counter++;
                    continue;
                }
                if (cmd[0] == 'c')
                {
                    fprintf(machFile, "%d ", cx);
                    cmd_array[cmd_counter] = cx;
                    cmd_counter++;
                    continue;
                }
                if (cmd[0] == 'd')
                {
                    fprintf(machFile, "%d ", dx);
                    
                    cmd_array[cmd_counter] = dx;
                    cmd_counter++;
                    
                    continue;
                }
                if (cmd[0] == 'e')
                {
                    fprintf(machFile, "%d ", ex);
                    
                    cmd_array[cmd_counter] = ex;
                    cmd_counter++;
                    
                    continue;
                }
                if (cmd[0] == 'f')
                {
                    fprintf(machFile, "%d ", fx);
                    
                    cmd_array[cmd_counter] = fx;
                    cmd_counter++;
                    
                    continue;
                }
                if (cmd[0] == 'g')
                {
                    fprintf(machFile, "%d ", gx);
                    cmd_array[cmd_counter] = gx;
                    cmd_counter++;
                    continue;
                }
                if (cmd[0] == 'h')
                {
                    fprintf(machFile, "%d ", hx);
                    cmd_array[cmd_counter] = hx;
                    cmd_counter++;
                    continue;
                }//make func for registers 
            }
            else
            {
                double command_arg;
                if(err) err = fprintf(machFile, "%d ", _cmd_push);
                cmd_array[cmd_counter] = (u_int32_t)_cmd_push;
                cmd_counter++;
                            
                if(err) err = fprintf(machFile, "%s ", cmd);
                
                cmd_array[cmd_counter] = atof(cmd);
                cmd_counter++;
            }

            nComands += 2;
            continue;
        }
        if (strcmp(cmd, "pop") == 0)
        {
            if(err) err = fprintf(machFile, "%d ", _cmd_pop);
            
            cmd_array[cmd_counter] = (u_int32_t)_cmd_pop;
                cmd_counter++;
            
            if(err) err = fscanf (asmFile,  "%s" , cmd);

            cmd_array[cmd_counter] = atof(cmd);
                cmd_counter++;
            
            if(err) err = fprintf(machFile, "%s ", cmd);
            
            nComands += 2;
            continue;
        }
        if (strcmp(cmd, "add") == 0)
        {
            if(err) err = fprintf(machFile, "%d ", _cmd_add);
            
            cmd_array[cmd_counter] = (u_int32_t)_cmd_add;
                cmd_counter++;
            
            nComands++;
            continue;
        }
        if (strcmp(cmd, "sub") == 0)
        {
            if(err) err = fprintf(machFile, "%d ", _cmd_sub);
            
            cmd_array[cmd_counter] = (u_int32_t)_cmd_sub;
                cmd_counter++;
            
            nComands++;
            continue;
        }
        if (strcmp(cmd, "mul") == 0)
        {
            if(err) err = fprintf(machFile, "%d ", _cmd_mul);
            cmd_array[cmd_counter] = (u_int32_t)_cmd_mul;
                cmd_counter++;
            nComands++;
            continue;
        }
        if (strcmp(cmd, "div") == 0)
        {
            if(err) err = fprintf(machFile, "%d ", _cmd_div);
            cmd_array[cmd_counter] = (u_int32_t)_cmd_div;
                cmd_counter++;
            nComands++;
            continue;
        }
        if (strcmp(cmd, "out") == 0)
        {
            if(err) err = fprintf(machFile, "%d ", _cmd_out);
            cmd_array[cmd_counter] = (u_int32_t)_cmd_out;
                cmd_counter++;
            nComands++;
            continue;
        }
        if (strcmp(cmd, "in") == 0)
        {
            if(err) err = fprintf(machFile, "%d ", _cmd_in);
            cmd_array[cmd_counter] = (u_int32_t)_cmd_in;
                cmd_counter++;
            nComands++;
            continue;
        }
        if (strcmp(cmd, "sqrt") == 0)
        {
            if(err) err = fprintf(machFile, "%d ", _cmd_sqrt);
            cmd_array[cmd_counter] = (u_int32_t)_cmd_sqrt;
                cmd_counter++;
            nComands++;
            continue;
        }
        if (strcmp(cmd, "sin") == 0)
        {
            if(err) err = fprintf(machFile, "%d ", _cmd_sin);
            cmd_array[cmd_counter] = (u_int32_t)_cmd_sin;
                cmd_counter++;
            nComands++;
            continue;
        }
        if (strcmp(cmd, "cos") == 0)
        {
            if(err) err = fprintf(machFile, "%d ", _cmd_cos);
            cmd_array[cmd_counter] = (u_int32_t)_cmd_cos;
                cmd_counter++;
            nComands++;
            continue;
        }
        if (strcmp(cmd, "dump") == 0)
        {
            if(err) err = fprintf(machFile, "%d ", _cmd_dump);
            cmd_array[cmd_counter] = (u_int32_t)_cmd_dump;
                cmd_counter++;
            nComands++;
            continue;
        }
        if (strcmp(cmd, "hlt") == 0)
        {
            if(err) err = fprintf(machFile, "%d ", _cmd_hlt);
            
            cmd_array[cmd_counter] = (u_int32_t)_cmd_hlt;
                cmd_counter++;
            
            nComands++;
            err = 0;
            continue;
        }
        if (strcmp(cmd, "jmp"))
        {
            if(err) err = fprintf(machFile, "%d ", _cmd_jmp);
            if(err) err = fscanf (asmFile,  "%s" , cmd);

            cmd_array[cmd_counter] = atof(cmd);
                cmd_counter++;
            
            if(err) err = fprintf(machFile, "%s ", cmd);
            nComands += 2;
            continue;
        }
        if (strcmp(cmd, "ja"))
        {
            if(err) err = fprintf(machFile, "%d ", _cmd_ja);
            if(err) err = fscanf (asmFile,  "%s" , cmd);

            cmd_array[cmd_counter] = atof(cmd);
                cmd_counter++;

            if(err) err = fprintf(machFile, "%s ", cmd);
            nComands += 2;
            continue;
        }
        if (strcmp(cmd, "jae"))
        {
            if(err) err = fprintf(machFile, "%d ", _cmd_jae);

            if(err) err = fscanf (asmFile,  "%s" , cmd);

            cmd_array[cmd_counter] = atof(cmd);
                cmd_counter++;

            if(err) err = fprintf(machFile, "%s ", cmd);
            nComands += 2;
            continue;
        }
        if (strcmp(cmd, "jb"))
        {
            if(err) err = fprintf(machFile, "%d ", _cmd_jb);

            if(err) err = fscanf (asmFile,  "%s" , cmd);

            cmd_array[cmd_counter] = atof(cmd);
                cmd_counter++;

            if(err) err = fprintf(machFile, "%s ", cmd);
            nComands += 2;
            continue;
        }
        if (strcmp(cmd, "jbe"))
        {
            if(err) err = fprintf(machFile, "%d ", _cmd_jbe);

            if(err) err = fscanf (asmFile,  "%s" , cmd);

            cmd_array[cmd_counter] = atof(cmd);
                cmd_counter++;

            if(err) err = fprintf(machFile, "%s ", cmd);
            nComands += 2;
            continue;
        }
        if (strcmp(cmd, "je"))
        {
            if(err) err = fprintf(machFile, "%d ", _cmd_je);

            if(err) err = fscanf (asmFile,  "%s" , cmd);

            cmd_array[cmd_counter] = atof(cmd);
                cmd_counter++;

            if(err) err = fprintf(machFile, "%s ", cmd);
            nComands += 2;
            continue;
        }
        if (strcmp(cmd, "jne"))
        {
            if(err) err = fprintf(machFile, "%d ", _cmd_jne);

            if(err) err = fscanf (asmFile,  "%s" , cmd);

            cmd_array[cmd_counter] = atof(cmd);
                cmd_counter++;

            if(err) err = fprintf(machFile, "%s ", cmd);
            nComands += 2;
            continue;
        }
        err = 0;
    }
    fprintf(machFile, "-1 ");
    nComands++;

    ///////////////////////////////////
    for (int i = 0; i < nComands; i++)
    {
        fprintf(stderr, "%x %lg\n", cmd_array[i], cmd_array[i]);
    }
    ///////////////////////////////////

    fseek(machFile, txt_sizeptr, SEEK_SET);
    fprintf(machFile, "%0*x\n", 8, nComands);
    
    fclose(machFile);
    fclose(asmFile);

    BinWrite(cmd_array, cmdFile, nComands);

    return;
}

void BinWrite(double* cmd_array, const char* BinFileName, u_int32_t nComands)
{
    FILE* binFile = fopen(BinFileName, "wb"); assert(binFile);
    fwrite(&signatura, sizeof(u_int32_t), 1, binFile);
    fwrite(&ass_version, sizeof(int), 1, binFile);
    fwrite(cmd_array, sizeof(double), nComands, binFile);
    fclose(binFile);
    free(cmd_array);
}

void labelCtor(labelArray_t* lblarr, int nlabels)
{

}