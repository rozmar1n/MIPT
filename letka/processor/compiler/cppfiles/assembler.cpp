#include"../headers/assembler.h"
//TODO: сделать битовые маски
//TODO: сделать видеопамять
void MakeMachCode(const char* ProgramFile, const char* cmdFile, const char* logFile, int iter, labelArray_t* labels)
{      

    FILE* machFile = fopen(logFile, "w");
    if (machFile == 0)
    {
        fprintf(stderr, "We couldn't open you logFile!!!\n");
        return;
    }

    long temp_size;
    char* cmd_buffer = PutText(ProgramFile, &temp_size);
    int amountOfComands = 0;
fprintf(stderr, "temp_size: %ld\n", temp_size);
    Strings* cmds_indexes = MakeIndex(cmd_buffer, &amountOfComands, temp_size);
fprintf(stderr, "problem not in MakeIndex\n");
    int assmIp = 0;


    fprintf(machFile, "%s\n", "ROST");
    fprintf(machFile, "%d\n", ass_version);

    long int txt_sizeptr = ftell(machFile);

        double* cmd_array = (double*)calloc(1024, sizeof(double));
        int cmd_counter = 0;

    for (int i = 0; i < 2*sizeof(unsigned int); i++)
    {
        fprintf(machFile, "0");
    }
    fprintf(machFile, "\n");

    char* cmd = NULL;
    int err = 1;
    u_int32_t nComands = 0;

fprintf(stderr, "before while\n");
    while(err)
    {
        cmd = cmds_indexes[assmIp++].string_start; 

        fprintf(stderr, "%s\n", cmd);
        if (strcmp(cmd, "push") == 0)
        {
            cmd = cmds_indexes[assmIp++].string_start;
            int reg = -1;
            reg = FillReg(cmd);
            if (reg != -1)
            {
                fprintf(machFile, "%d ", cmd_pushr);
                cmd_array[cmd_counter] = cmd_pushr;
                cmd_counter++;

                fprintf(machFile, "%d ", reg);
                cmd_array[cmd_counter] = reg;
                cmd_counter++;
            }
            else
            {
                fprintf(machFile, "%d ", cmd_push);
                
                cmd_array[cmd_counter] = (u_int32_t)cmd_push;
                cmd_counter++;
                
                fprintf(machFile, "%s ", cmd);
                cmd_array[cmd_counter] = atof(cmd);
                cmd_counter++;
            }
            nComands += 2;
            continue;
        }

        if (strcmp(cmd, "pop") == 0)
        {
            if(err) err = fprintf(machFile, "%d ", cmd_pop);
            
            cmd_array[cmd_counter] = (u_int32_t)cmd_pop;
                cmd_counter++;
            
            cmd = cmds_indexes[assmIp++].string_start;

            int reg = -1;
            reg = FillReg(cmd);
            if (reg != -1)
            {
                fprintf(machFile, "%d ", reg);
                cmd_array[cmd_counter] = reg;
                cmd_counter++;
            }
            else
            {
                fprintf(stderr, "UNDEFINED COMMAND!!!\n");
            }
            nComands += 2;
            continue;
        }
        if (strcmp(cmd, "add") == 0)
        {
            if(err) err = fprintf(machFile, "%d ", cmd_add);
            
            int temp_cmd = cmd_add;
            memcpy(&(cmd_array[cmd_counter++]), &temp_cmd, sizeof(double));
            
            
            nComands++;
            continue;
        }
        if (strcmp(cmd, "sub") == 0)
        {
            if(err) err = fprintf(machFile, "%d ", cmd_sub);
            
            int temp_cmd = cmd_sub;
            memcpy(&(cmd_array[cmd_counter++]), &temp_cmd, sizeof(double));
            
            nComands++;
            continue;
        }
        if (strcmp(cmd, "mul") == 0)
        {
            if(err) err = fprintf(machFile, "%d ", cmd_mul);
            int temp_cmd = cmd_mul;
            memcpy(&(cmd_array[cmd_counter++]), &temp_cmd, sizeof(double));
            nComands++;
            continue;
        }
        if (strcmp(cmd, "div") == 0)
        {
            if(err) err = fprintf(machFile, "%d ", cmd_div);
            int temp_cmd = cmd_div;
            memcpy(&(cmd_array[cmd_counter++]), &temp_cmd, sizeof(double));
            nComands++;
            continue;
        }
        if (strcmp(cmd, "out") == 0)
        {
            if(err) err = fprintf(machFile, "%d ", cmd_out);
            int temp_cmd = cmd_out;
            memcpy(&(cmd_array[cmd_counter++]), &temp_cmd, sizeof(double));
            nComands++;
            continue;
        }
        if (strcmp(cmd, "in") == 0)
        {
            if(err) err = fprintf(machFile, "%d ", cmd_in);
            int temp_cmd = cmd_in;
            memcpy(&(cmd_array[cmd_counter++]), &temp_cmd, sizeof(double));
            nComands++;
            continue;
        }
        if (strcmp(cmd, "sqrt") == 0)
        {
            if(err) err = fprintf(machFile, "%d ", cmd_sqrt);
            int temp_cmd = cmd_sqrt;
            memcpy(&(cmd_array[cmd_counter++]), &temp_cmd, sizeof(double));
            nComands++;
            continue;
        }
        if (strcmp(cmd, "sin") == 0)
        {
            if(err) err = fprintf(machFile, "%d ", cmd_sin);
            int temp_cmd = cmd_sin;
            memcpy(&(cmd_array[cmd_counter++]), &temp_cmd, sizeof(double));
            nComands++;
            continue;
        }
        if (strcmp(cmd, "cos") == 0)
        {
            if(err) err = fprintf(machFile, "%d ", cmd_cos);
            
            int temp_cmd = cmd_cos;
            memcpy(&(cmd_array[cmd_counter++]), &temp_cmd, sizeof(double));
            
            nComands++;
            continue;
        }
        if (strcmp(cmd, "dump") == 0)
        {
            if(err) err = fprintf(machFile, "%d ", cmd_dump);
            int temp_cmd = cmd_dump;
            memcpy(&(cmd_array[cmd_counter++]), &temp_cmd, sizeof(double));
            nComands++;
            continue;
        }
        if (strcmp(cmd, "hlt") == 0)
        {
            if(err) err = fprintf(machFile, "%d ", cmd_hlt);
            
            int temp_cmd = cmd_hlt;
            memcpy(&(cmd_array[cmd_counter++]), &temp_cmd, sizeof(double));
            
            nComands++;
            //err = 0;
            continue;
        }
        if (strcmp(cmd, "jmp") == 0)
        {
            if(err) err = fprintf(machFile, "%d ", cmd_jmp);
            cmd_array[cmd_counter] = cmd_jmp;
                cmd_counter++;
            cmd = cmds_indexes[assmIp++].string_start;

            if (strchr(cmd, ':'))
            {
                cmd_array[cmd_counter] = TakeLabel(labels, cmd);
                fprintf(machFile, "%lg ", cmd_array[cmd_counter]);
                cmd_counter++;
            }
            else
            {
                cmd_array[cmd_counter] = atof(cmd);
                cmd_counter++;
                fprintf(machFile, "%s ", cmd);
            }
            
            nComands += 2;
            continue;
        }
        if (strcmp(cmd, "ja") == 0)
        {
            if(err) err = fprintf(machFile, "%d ", cmd_ja);
            cmd_array[cmd_counter] = cmd_ja;
                cmd_counter++;
            cmd = cmds_indexes[assmIp++].string_start;

            if (strchr(cmd, ':'))
            {
                cmd_array[cmd_counter] = TakeLabel(labels, cmd);
                fprintf(machFile, "%lg ", cmd_array[cmd_counter]);
                cmd_counter++;
            }
            else
            {
                cmd_array[cmd_counter] = atof(cmd);
                cmd_counter++;
                fprintf(machFile, "%s ", cmd);
            }

            nComands += 2;
            continue;
        }
        if (strcmp(cmd, "jae") == 0)
        {
            if(err) err = fprintf(machFile, "%d ", cmd_jae);
            cmd_array[cmd_counter] = cmd_jae;
                cmd_counter++;
            cmd = cmds_indexes[assmIp++].string_start;

            if (strchr(cmd, ':'))
            {
                cmd_array[cmd_counter] = TakeLabel(labels, cmd);
                fprintf(machFile, "%lg ", cmd_array[cmd_counter]);
                cmd_counter++;
            }
            else
            {
                cmd_array[cmd_counter] = atof(cmd);
                cmd_counter++;
                fprintf(machFile, "%s ", cmd);
            }

            if(err) err = fprintf(machFile, "%s ", cmd);
            nComands += 2;
            continue;
        }
        if (strcmp(cmd, "jb") == 0)
        {
            if(err) err = fprintf(machFile, "%d ", cmd_jb);
            cmd_array[cmd_counter] = cmd_jb;
                cmd_counter++;
            cmd = cmds_indexes[assmIp++].string_start;
            if (strchr(cmd, ':'))
            {
                cmd_array[cmd_counter] = TakeLabel(labels, cmd);
                fprintf(machFile, "%lg ", cmd_array[cmd_counter]);
                cmd_counter++;
            }
            else
            {
                cmd_array[cmd_counter] = atof(cmd);
                cmd_counter++;
                fprintf(machFile, "%s ", cmd);
            }
            
            nComands += 2;
            continue;
        }
        if (strcmp(cmd, "jbe") == 0)
        {
            if(err) err = fprintf(machFile, "%d ", cmd_jbe);
            cmd_array[cmd_counter] = cmd_jbe;
                cmd_counter++;
            cmd = cmds_indexes[assmIp++].string_start;

            if (strchr(cmd, ':'))
            {
                cmd_array[cmd_counter] = TakeLabel(labels, cmd);
                fprintf(machFile, "%lg ", cmd_array[cmd_counter]);
                cmd_counter++;
            }
            else
            {
                cmd_array[cmd_counter] = atof(cmd);
                cmd_counter++;
                fprintf(machFile, "%s ", cmd);
            }

            if(err) err = fprintf(machFile, "%s ", cmd);
            nComands += 2;
            continue;
        }
        if (strcmp(cmd, "je") == 0)
        {
            if(err) err = fprintf(machFile, "%d ", cmd_je);
            cmd_array[cmd_counter] = cmd_je;
                cmd_counter++;
            cmd = cmds_indexes[assmIp++].string_start;

            if (strchr(cmd, ':'))
            {
                cmd_array[cmd_counter] = TakeLabel(labels, cmd);
                fprintf(machFile, "%lg ", cmd_array[cmd_counter]);
                cmd_counter++;
            }
            else
            {
                cmd_array[cmd_counter] = atof(cmd);
                cmd_counter++;
                fprintf(machFile, "%s ", cmd);
            }

            if(err) err = fprintf(machFile, "%s ", cmd);
            nComands += 2;
            continue;
        }
        if (strcmp(cmd, "jne") == 0)
        {
            if(err) err = fprintf(machFile, "%d ", cmd_jne);
            cmd_array[cmd_counter] = cmd_jne;
                cmd_counter++;
            cmd = cmds_indexes[assmIp++].string_start;

            if (strchr(cmd, ':'))
            {
                cmd_array[cmd_counter] = TakeLabel(labels, cmd);
                fprintf(machFile, "%lg ", cmd_array[cmd_counter]);
                cmd_counter++;
            }
            else
            {
                cmd_array[cmd_counter] = atof(cmd);
                cmd_counter++;
                fprintf(machFile, "%s ", cmd);
            }

            if(err) err = fprintf(machFile, "%s ", cmd);
            nComands += 2;
            continue;
        }
        if (strchr(cmd, ':'))
        {
            if(!IsLabel(labels, cmd))
            {
                MakeLabel(labels, cmd, nComands++);
            }
            continue;
        }
        err = 0;
    }

    ///////////////////////////////////
    // for (int i = 0; i < nComands; i++)
    // {
    //     fprintf(stderr, "%x %lg\n", cmd_array[i], cmd_array[i]);
    // }
    ///////////////////////////////////

    fseek(machFile, txt_sizeptr, SEEK_SET);
    fprintf(machFile, "%0*x\n", 8, nComands);
    
    fclose(machFile);

    fprintf(stderr, "first dump: \n");
    LabelDump(labels);
    if (iter == 2)
    {
        BinWrite(cmd_array, cmdFile, nComands);
        LabelDtor(labels);
    }
    fprintf(stderr, "second dump: \n");
    LabelDump(labels);
    return;
}

int FillReg(char* cmd)
{
    if(strchr(cmd, 'x'))
    {
        if (strchr(cmd, 'a')) return ax;
        if (strchr(cmd, 'b')) return bx;
        if (strchr(cmd, 'c')) return cx;
        if (strchr(cmd, 'd')) return dx;
        if (strchr(cmd, 'e')) return ex;
        if (strchr(cmd, 'f')) return fx;
        if (strchr(cmd, 'g')) return gx;
        if (strchr(cmd, 'h')) return hx;
        
        return -1;
    }
    else
    {
        return -1;
    }
}

void BinWrite(double* cmd_array, const char* BinFileName, u_int32_t nComands)
{
    FILE* binFile = fopen(BinFileName, "wb"); assert(binFile);//TODO: обработать fopen без ассерта 
    
    fwrite(&signatura, sizeof(u_int32_t), 1, binFile); //TODO: if(fwrite == 0) goto close
    fwrite(&ass_version, sizeof(int), 1, binFile);
    fwrite(&nComands, sizeof(u_int32_t), 1, binFile);

    fwrite(cmd_array, sizeof(double), nComands, binFile);//TODO: обработать 
    fclose(binFile);
    
    fprintf(stderr, "\n\n\n\t\033[46mArrayDump\033[0m\n");
    for (int i = 0; i < nComands; i++)
    {
        fprintf(stderr, "%lg  ", cmd_array[i]);
    }
    

    free(cmd_array);
}

void LabelCtor(labelArray_t* lblarr, int nlabels)
{
    lblarr->array = (label_t*)calloc(nlabels, sizeof(label_t));
    lblarr->used_labels = 0;
    for (size_t i = 0; i < nlabels; i++)
    {
        for (size_t j = 0; j < 128; j++)
        {
            lblarr->array[i].label_name[j] = '\0';
        }
        lblarr->array[i].line_number = -1;
    }
}

void LabelDtor(labelArray_t* lblarr)
{
    free(lblarr->array);
    lblarr->used_labels = -1;
}

void LabelDump(labelArray_t* lblarr)
{
    fprintf(stderr, "-----------------------------------------------------------------------------------------------------------------------------------------------------\n"
                    "\n//////////---LabelDump---//////////\n");
    
    for (int i = 0; i < amount_of_labels; i++)
    {
        fprintf(stderr, "lbl name: %s; line_number: %d\n", lblarr->array[i].label_name, lblarr->array[i].line_number);
    }
    fprintf(stderr, "number of used labels: %u\n", lblarr->used_labels);
    fprintf(stderr, "-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

void MakeLabel(labelArray_t* lblarr, char* labelName, int lineNumber)
{
    strcpy(lblarr->array[lblarr->used_labels].label_name, labelName);
    lblarr->array[lblarr->used_labels].line_number = lineNumber;
    lblarr->used_labels++;
}

double TakeLabel(labelArray_t* lblarr, char* labelName)
{
    double ret_line;
    for (int i = 0; i < lblarr->used_labels; i++)
    {
        if (strcmp(labelName, lblarr->array[i].label_name) == 0)
        {
            return lblarr->array[i].line_number;
        }
    }
    return -1;
}

int    IsLabel (labelArray_t* lblarr, char* labelName)
{
    for (int i = 0; i < lblarr->used_labels; i++)
    {
        if (strcmp(labelName, lblarr->array[i].label_name) == 0)
        {
            return 1;
        }
    }
    return 0;
}

void WritePushArgs(char* cmd)
{

}